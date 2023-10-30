#ifndef COLLISION_TEST_3D_H
#define COLLISION_TEST_3D_H
#include "../../../Game/Game.h"
#include <array>



struct Collider {
	virtual Vec3 FindFurthestPoint(Vec3 direction) const = 0;
};



/// <summary>
/// https://www.youtube.com/watch?v=MDusDn8oTSE 
/// 5:33
/// </summary>
struct MeshCollider : Collider{
private:
	std::vector<Vec3> _vertices;
public :
	Vec3 FindFurthestPoint(Vec3 direction) const override{
		Vec3 maxPoint;
		float maxDistance = -FLT_MAX;

		for (Vec3 vertex : _vertices) {
			float distance = Vec3::Dot(vertex, direction);
			if (distance > maxDistance) {
				maxDistance = distance; 
				maxPoint = vertex;
			}
		}
		return maxPoint;
	}
};



struct Simplex {

private:
	std::array<Vec3, 4> m_points;
	unsigned int m_size;

public :
	Simplex() :
		m_points({ Vec3(), Vec3(), Vec3(), Vec3()}),
		m_size(0) {
	}
	
	Simplex& operator=(std::initializer_list<Vec3> list){
		for (auto v = list.begin(); v != list.end(); v++) {
			m_points[std::distance(list.begin(), v)] = *v;
		}
		m_size = list.size();
		return *this;
	}

	void push_front(Vec3 point) {
		m_points = {point, m_points[0], m_points[1], m_points[2]};
		m_size = std::min(m_size + 1, 4u);
	}

	//23 movember 12th
	Vec3& operator[](unsigned int i) { return m_points[i]; }
	unsigned int size() const {
		return m_size;
	}
	auto begin() const {
		return m_points.begin();
	}
	auto end() const {
		return m_points.end() - (4 - m_size);
	}

};




class CollisionTest3D : public Game {

private:
	bool Triangle(Simplex& points, Vec3& direction) {
		
		Vec3 a = points[0];
		Vec3 b = points[1];
		Vec3 c = points[2];

		Vec3 ab = b - a;
		Vec3 ac = c - a;
		Vec3 ao = a * -1;

		Vec3 abc = Vec3::Cross(ab, ac);

		if (SameDirection(Vec3::Cross(abc, ac), ao)) {
			if (SameDirection(ac, ao)) {
				points = { a, c };
				direction = Vec3::Cross(Vec3::Cross(ac, ao), ac);
			}
			else {
				return Line(points = { a, b }, direction);
			}
		}
		else {
			if ( SameDirection( Vec3::Cross(ab, abc), ao) ) {
				return Line(points = { a, b }, direction);
			}
			else {
				if (SameDirection(abc, ao) ){
					direction = abc;
				}
				else {
					points = { a, c, b };
					direction = abc * -1;
				}
				
			}
		}

		return false;
	}
	bool Line(Simplex& points, Vec3 direction) {
		Vec3 a = points[0];
		Vec3 b = points[1];

		Vec3 ab = b - a;
		Vec3 ao = a*-1;

		if (SameDirection(ab, ao)) {
			direction = Vec3::Cross(Vec3::Cross(ab, ao), ab);
		}
		else {
			points = { a };
			direction = ao;
		}

		return false;
	}

	bool Tetrahedron(Simplex& points, Vec3& direction) {

		Vec3 a = points[0];
		Vec3 b = points[1];
		Vec3 c = points[2];
		Vec3 d = points[3];
		
		Vec3 ab = b - a;
		Vec3 ac = c - a;
		Vec3 ad = d - a;
		Vec3 ao = a * -1;

		Vec3 abc = Vec3::Cross(ab, ac);
		Vec3 acd = Vec3::Cross(ac, ad);
		Vec3 adb = Vec3::Cross(ad, ab);

		if (SameDirection(abc, ao)) {
			return Triangle(points = { a, b, c }, direction);
		}
		if (SameDirection(acd, ao)) {
			return Triangle(points = { a, c, d }, direction);
		}
		if (SameDirection(adb, ao)) {
			return Triangle(points = { a, d, b }, direction);
		}

		return true;
	}
	bool SameDirection(const Vec3& direction, const Vec3& ao) {
		return Vec3::Dot(direction, ao) > 0;
	}
	bool NextSimplex(Simplex& points, Vec3& direction) {
		switch (points.size())
		{
		case 2: return Line			(points, direction);
		case 3: return Triangle		(points, direction);
		case 4: return Tetrahedron	(points, direction);
		default:
			break;
		}
		//never should be 
		return false;
	}

	Vec3 Support(const Collider* colliderA, const Collider* colliderB, Vec3 direction) {
		return colliderA->FindFurthestPoint(direction) - colliderB->FindFurthestPoint(direction * -1.0f);
	}
	bool GJK(const Collider* colliderA, const Collider* colliderB) {
		//get initial support point in any direction
		Vec3 support = Support(colliderA, colliderB, Vec3(1.0f, 0.0f, 0.0f));


		//simplex is an array of points, max count is 4
		Simplex points;
		points.push_front(support);

		//new direction is towards the origin
		Vec3 direction = support * -1;

		while (true) {
			support = Support(colliderA, colliderB, direction);

			if (Vec3::Dot(support, direction) <= 0) {
				return false;//no collision
			}
			
			points.push_front(support);

			if (NextSimplex(points, direction)) {
				return true;
			}
		}
	}
public :
	CollisionTest3D();
	~CollisionTest3D();
	void Update(float deltaTime) override;
	void MoveCamera();


};
#endif // !MESH_TEST_H
