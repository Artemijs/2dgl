#ifndef COLLISION_TEST_3D_H
#define COLLISION_TEST_3D_H
#include "../../../Game/Game.h"



struct Collider {
	virtual Vec3 FindFurthestPoint(Vec3 direction) const = 0;
};



/// <summary>
/// https://www.youtube.com/watch?v=MDusDn8oTSE 
/// 2:53
/// </summary>
struct MeshCollider : Collider{
private:
	std::vector<Vec3> _vertices;
public :
	Vec3 FindFurthestPoint(Vec3 direction) const override{
		Vec3 maxPoint;
		float maxDistance = -FLT_MAX;

		for (Vec3 vertex : _vertices) {
			float distance = Vec3::Dot(vertex,direction);
			if (distance > maxDistance) {
				maxDistance = distance; 
				maxPoint = vertex;
			}
		}
		return maxPoint;
	}
};



class CollisionTest3D : public Game {

private:

public :
	CollisionTest3D();
	~CollisionTest3D();
	void Update(float deltaTime) override;
	void MoveCamera();

};
#endif // !MESH_TEST_H
