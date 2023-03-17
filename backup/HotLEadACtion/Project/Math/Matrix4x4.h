#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H

class Vec2
{
private:

public:
	float x, y;
	Vec2();
	Vec2(float x, float y);
	Vec2 operator+(const Vec2& v);
	Vec2 operator*(const float f);
	void operator+=(const  Vec2& v);
	bool operator==(const Vec2& v);
	void operator=(const Vec2& v);

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
	bool operator==(const Vec2Int& v);
	void operator=(const Vec2Int& v);

};
class Vec3
{
private:

public:
	float x, y, z;
	Vec3();
	Vec3(float x, float y, float z);
	Vec3 operator+(const Vec3& v);
	Vec3 operator-(const Vec3& v);
	Vec3 operator/(const float f);
	Vec3 operator*(const float f);
	void operator+=(const float& n);
	void operator+=(const int& n);
	void operator+=(const  Vec3& v);
	void operator-=(const  Vec3& v);
	void operator/=(const  float& v);
	
	float Lenght();
	void Normalize();
	static void Normalize( Vec3& vec);
	float DistanceTo(const Vec3& other);
};
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

class Matrix4x4 {
	
public:
	float buff[16] = { 0,0,0,0,
						 0,0,0,0,
						 0,0,0,0,
						 0,0,0,1 };
	Matrix4x4();
	Matrix4x4(const Matrix4x4& m);
	Matrix4x4(float n);
	//~Matrix4x4();
	void SetTranslation(Vec3 v);
	void SetScale(Vec3 s);
	Matrix4x4 operator+(const Matrix4x4& m);
	Matrix4x4 operator-(const Matrix4x4& m);
	Matrix4x4 operator*(const Matrix4x4& m);
	//Matrix4x4 operator*=(const Matrix4x4& m);
	Vec4 operator*(const Vec4& v);
	void SetRotation(float ang);
	static Matrix4x4 Ortho(float left, float right, float bot, float top, float near, float far);
	static Matrix4x4 RotationMatrix(float ang);
	static Matrix4x4 ScaleMatrix(Vec3 scale);
	static Matrix4x4 TranslationMatrix(Vec3 pos);
	//float GetAngle();
	Vec3 GetPosition();
	Vec3 GetSize();

};
#endif