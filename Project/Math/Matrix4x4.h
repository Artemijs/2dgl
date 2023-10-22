#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H

class Vec2
{
private:

public:
	float x, y;
	Vec2();
	Vec2(float x, float y);
	Vec2 operator+(const Vec2& v) const;
	Vec2 operator-(const Vec2& v) const;
	Vec2 operator*(const float f) const;
	Vec2 operator/(const float f) const;
	void operator+=(const  Vec2& v);
	bool operator==(const Vec2& v) const;
	void operator=(const Vec2& v);
	void operator/=(const float f);

	void Normalize();
	static const Vec2 Normalize(const Vec2 &v);
	static const float Distance(const Vec2 &a, const Vec2 &b);
	static const float Distance(const float ax, const float ay, const float bx, const float by);
	static const float Lenght(const Vec2 &v);
	static const float Dot(const Vec2& a, const Vec2& b);
	static const float Dot(const float ax, const float ay, const float bx, const float by);
	static const Vec2 LineIntersection(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d);

};
class Vec2Int
{
private:

public:
	int x, y;
	Vec2Int();
	Vec2Int(int x, int y);
	Vec2Int operator+(const Vec2Int& v);
	Vec2Int operator*(const int f);
	void operator+=(const  Vec2Int& v);
	bool operator==(const Vec2Int& v)const;
	void operator=(const Vec2Int& v);

};

class Vec3
{
private:

public:
	float x, y, z;
	Vec3();
	Vec3(float x, float y, float z);
	const Vec3 operator+(const Vec3& v)const ;
	const Vec3 operator-(const Vec3& v)const;
	const Vec3 operator/(const float f)const;
	const Vec3 operator*(const float f)const;
	friend const Vec3 operator*(const float lhs, const Vec3& rhs) {
		return Vec3(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
	}
	friend const Vec3 operator/(const float lhs, const Vec3& rhs) {
		return Vec3(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs);
	}
	void operator+=(const float& n);
	void operator+=(const int& n);
	void operator+=(const  Vec3& v);
	void operator-=(const  Vec3& v);
	void operator/=(const  float& v);
	const bool operator==(const Vec3& v) const;
	void operator=(const Vec3& v) ;
	const float Lenght()const;
	void Normalize();
	static const Vec3 Normalize(const Vec3& vec) ;
	const float DistanceTo(const Vec3& other);
	static const float Distance(const Vec3& a, const Vec3& b);
	static const float Distance(const float ax, const float ay, const float az,const float bx, const float by, const float bz);
	static const float Lenght(const Vec3& v);
	static Vec3 Cross(const Vec3& a, const Vec3& b);
	static float Dot(const Vec3& a, const Vec3& b);
	//friend class Float;
};
/*
Vec3 operator*(const float& lhs, const Vec3& rhs) {
	
	return Vec3(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}
Vec3 operator/(const float& lhs, const Vec3& rhs) {

	return Vec3(rhs.x / lhs, rhs.y / lhs, rhs.z /lhs);
}*/
class Vec4
{
private:
	
public:
	float x, y, z, a;
	Vec4();
	Vec4(float x, float y, float z, float a = 0);
	Vec4 operator+(const Vec4& v);
	Vec4 operator*(const float f);
	void operator+=(const Vec4& v);
};

class Matrix3x3 {

public:
	float buff[9] = {   0,0,0,
						0,0,0,
						0,0,0
	};
	Matrix3x3();
	Matrix3x3(const Matrix3x3& m);
	Matrix3x3(float n);
	Matrix3x3 operator+(const Matrix3x3& m)const;
	Matrix3x3 operator-(const Matrix3x3& m)const;
	Matrix3x3 operator*(const Matrix3x3& m)const;
	static Matrix3x3 RotationMatrix(const float rotation, const Vec3& axis);
	//Matrix4x4 operator*=(const Matrix4x4& m);
	Vec3 operator*(const Vec3& v);
	const Vec3 operator*(const Vec3& v)const;
};



class Matrix4x4 {
	
public:
	float buff[16] = {   0,0,0,0,
						 0,0,0,0,
						 0,0,0,0,
						 0,0,0,1 
	};
	Matrix4x4();
	Matrix4x4(const Matrix4x4& m);
	Matrix4x4(float n);
	//~Matrix4x4();
	void SetTranslation(Vec3 v);
	void SetScale(Vec3 s);
	Matrix4x4 operator+(const Matrix4x4& m)const;
	Matrix4x4 operator-(const Matrix4x4& m)const;
	Matrix4x4 operator*(const Matrix4x4& m)const;
	//Matrix4x4 operator*=(const Matrix4x4& m);
	Vec4 operator*(const Vec4& v);
	//technically uses a vec4 here i just hard code a 1 for the 4th position in the vector
	Vec3 operator*(const Vec3& v);
	const Vec3 operator*(const Vec3& v)const ;
	void SetRotation(float ang);
	static Matrix4x4 Ortho(float left, float right, float bot, float top, float near, float far);
	static Matrix4x4 Perspective(const float fov, const float aspect, const float near, const float far);
	static Matrix4x4 RotationMatrix(float ang);
	static Matrix4x4 ScaleMatrix(Vec3 scale);
	static Matrix4x4 TranslationMatrix(Vec3 pos);
	static Matrix4x4 GetMatrix(Vec3 pos, Vec3 scale, float ang);
	static Matrix4x4 GetCameraMatrix(const Vec3& X, const Vec3& Y, const Vec3& Z, const Vec3& O);
	static Matrix4x4 RotationMatrix(const float rotation, const Vec3& axis);
	static Matrix4x4 RotationMatrix(Quaternion q);
	//float GetAngle();
	Vec3 GetPosition() const;
	Vec3 GetSize() const;

};



class Quaternion {
public  :
	float _x, _y, _z, _w;
	/// <summary>
	/// Initializes the quaternion
	/// </summary>
	/// <param name="Angle">in radians</param>
	/// <param name="V">axis</param>
	Quaternion(float Angle, const Vec3& V);
	Quaternion(float _x, float _y, float _z, float _w);
	/// <summary>
	/// Initialise the quaternion using Euler angles
	/// </summary>
	/// <param name="_x"></param>
	/// <param name="_y"></param>
	/// <param name="_z"></param>
	Quaternion(float _x, float _y, float _z);
	void Normalize();
	Quaternion Conjugate() const;
	friend Quaternion operator*(const Quaternion& q, const Vec3& v);
	friend Quaternion operator*(const Quaternion& l, const Quaternion& r);
	void FromEulerAngles(const float x, const float y, const float z);
	Vec3 GetEulerAngles();
	Vec3 ToDegrees();
};



struct RayHitData {
	
};


class Ray {

public :
	float _distance;
	Vec3 _direction;
	Vec3 _position;
	Ray();
	Ray(float dist, Vec3 dir, Vec3 pos);
	~Ray();
};

#endif