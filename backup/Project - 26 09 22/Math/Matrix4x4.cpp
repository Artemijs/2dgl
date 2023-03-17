#include "Matrix4x4.h"
#include <iostream>


Vec2::Vec2() {
	x = 0; y = 0;
}
Vec2::Vec2(float mx, float my) {
	x = mx;
	y = my;
}
bool Vec2::operator==(const Vec2& v) {
	return (v.x == x && v.y == y);
}
void Vec2::operator=(const Vec2& v) {
	x = v.x;
	y = v.y;
}
Vec2 Vec2::operator+(const Vec2& v) {
	return Vec2(x + v.x, y + v.y);
}
Vec2 Vec2::operator*(float f) {
	return Vec2(x * f, y * f);
}
void Vec2::operator+=(const Vec2& v) {
	x += v.x;
	y += v.y;
}


Vec2Int::Vec2Int() {
	x = 0; y = 0;
}
Vec2Int::Vec2Int(int mx, int my) {
	x = mx;
	y = my;
}
bool Vec2Int::operator==(const Vec2Int& v) {
	return (v.x == x && v.y == y);
}
void Vec2Int::operator=(const Vec2Int& v) {
	x = v.x;
	y = v.y;
}
Vec2Int Vec2Int::operator+(const Vec2Int& v) {
	return Vec2Int(x + v.x, y + v.y);
}
Vec2Int Vec2Int::operator*(int f) {
	return Vec2Int(x * f, y * f);
}
void Vec2Int::operator+=(const Vec2Int& v) {
	x += v.x;
	y += v.y;
}


Vec3::Vec3() {
	x = 0; y = 0; z = 0;
}
Vec3::Vec3(float mx, float my, float mz) {
	x = mx;
	y = my;
	z = mz;
}
Vec3 Vec3::operator+(const Vec3& v) {
	return Vec3(x + v.x, y + v.y, z + v.z);
}
Vec3 Vec3::operator-(const Vec3& v) {
	return Vec3(x - v.x, y - v.y, z - v.z);
}
Vec3 Vec3::operator*(float f) {
	return Vec3(x * f, y * f, z * f);
}

void Vec3::operator+=(const float& n) {
	x += n;
	y += n;
	z += n;
}
void Vec3::operator+=(const int& n) {
	x += n;
	y += n;
	z += n;
}
void Vec3::operator+=(const Vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void Vec3::operator-=(const Vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
void Vec3::operator/=(const float& v) {
	x /= v;
	y /= v;
	z /= v;
}
Vec3 Vec3::operator/(const float f) {
	return Vec3(x / f, y / f, z / f);
}
float Vec3::Lenght() {
	return std::sqrt((x * x + y * y + z * z));
}

void Vec3::Normalize() {
	(*this) /= Lenght();
}
void Vec3::Normalize( Vec3& vec) {
	vec /= vec.Lenght();
}
float Vec3::DistanceTo(const Vec3& other) {
	return Vec3(x - other.x, y - other.y, z - other.z).Lenght();
}

Vec4::Vec4() {
	x = 0; y = 0; z = 0; a = 1;
}
Vec4::Vec4(float x, float y, float z, float a) {
	this->x = x; this->y = y; this->z = z; this->a = a;
}
void Vec4::operator+=(const Vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	a += v.a;
}
Vec4 Vec4::operator+(const Vec4& v) {
	return Vec4(x + v.x, y + v.y, z + v.z, a + v.a);
}
Vec4 Vec4::operator*(const float f) {
	return Vec4(x * f, y * f, z * f, a * f);
}
Matrix4x4::Matrix4x4(const Matrix4x4& m) {
	for (int i = 0; i < 16; i++) {
		buff[i] = m.buff[i];
	}
}
Matrix4x4::Matrix4x4() {
}
Matrix4x4::Matrix4x4(float n) {
	buff[0] = 1;
	buff[5] = 1;
	buff[10] = 1;
	/*
	0 1 2 3
	4 5 6 7
	8 9 10 11
	0 0 0 1
	*/
	
}
/*Matrix4x4::~Matrix4x4() {
	std::cout << "deleting mat\n";
	delete buff;
}*/
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m) {
	Matrix4x4 rm = Matrix4x4();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] + buff[i];
	}
	return rm;
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& m) {
	Matrix4x4 rm = Matrix4x4();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] - buff[i];
	}
	return rm;
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) {
	Matrix4x4 rm = Matrix4x4();
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15
	*/
	//r1 x c1
	rm.buff[0] = buff[0] * m.buff[0] + buff[1] * m.buff[4] + buff[2] * m.buff[8] + buff[3] * m.buff[12];
	//r2 x c1
	rm.buff[4] = buff[4] * m.buff[0] + buff[5] * m.buff[4] + buff[6] * m.buff[8] + buff[7] * m.buff[12];
	//r3 x c1
	rm.buff[8] = buff[8] * m.buff[0] + buff[9] * m.buff[4] + buff[10] * m.buff[8] + buff[11] * m.buff[12];
	//r4 x c1
	rm.buff[12] = buff[12] * m.buff[0] + buff[13] * m.buff[4] + buff[14] * m.buff[8] + buff[15] * m.buff[12];
	
	//r1 x c2
	rm.buff[1] = buff[0] * m.buff[1] + buff[1] * m.buff[5] + buff[2] * m.buff[9] + buff[3] * m.buff[13];
	//r2 x c2
	rm.buff[5] = buff[4] * m.buff[1] + buff[5] * m.buff[5] + buff[6] * m.buff[9] + buff[7] * m.buff[13];
	//r3 x c2
	rm.buff[9] = buff[8] * m.buff[1] + buff[9] * m.buff[5] + buff[10] * m.buff[9] + buff[11] * m.buff[13];
	//r4 x c2
	rm.buff[13] = buff[12] * m.buff[1] + buff[13] * m.buff[5] + buff[14] * m.buff[9] + buff[15] * m.buff[13];

	//r1 x c3
	rm.buff[2] = buff[0] * m.buff[2] + buff[1] * m.buff[6] + buff[2] * m.buff[10] + buff[3] * m.buff[14];
	//r2 x c3
	rm.buff[6] = buff[4] * m.buff[2] + buff[5] * m.buff[6] + buff[6] * m.buff[10] + buff[7] * m.buff[14];
	//r3 x c3
	rm.buff[10] = buff[8] * m.buff[2] + buff[9] * m.buff[6] + buff[10] * m.buff[10] + buff[11] * m.buff[14];
	//r4 x c3
	rm.buff[14] = buff[12] * m.buff[2] + buff[13] * m.buff[6] + buff[14] * m.buff[10] + buff[15] * m.buff[14];
	//r1 x c4
	rm.buff[3] = buff[0] * m.buff[3] + buff[1] * m.buff[7] + buff[2] * m.buff[11] + buff[3] * m.buff[15];
	//r2 x c4
	rm.buff[7] = buff[4] * m.buff[3] + buff[5] * m.buff[7] + buff[6] * m.buff[11] + buff[7] * m.buff[15];
	//r3 x c4
	rm.buff[11] = buff[8] * m.buff[3] + buff[9] * m.buff[7] + buff[10] * m.buff[11] + buff[11] * m.buff[15];
	//r4 x c4
	rm.buff[15] = buff[12] * m.buff[3] + buff[13] * m.buff[7] + buff[14] * m.buff[11] + buff[15] * m.buff[15];

	return rm;
}
Vec4 Matrix4x4::operator* (const Vec4& v) {
	Vec4 v4 = Vec4();
	v4.x = buff[0] * v.x + buff[1] * v.y + buff[2] * v.z + buff[3] * v.a;
	//r2 x c1
	v4.y = buff[4] * v.x + buff[5] * v.y + buff[6] * v.z + buff[7] * v.a;
	//r3 x c1
	v4.z = buff[8] * v.x + buff[9] * v.y + buff[10] * v.z + buff[11] * v.a;
	//r4 x c1
	v4.a = buff[12] * v.x + buff[13] * v.y + buff[14] * v.z + buff[15] * v.a;

	return v4;
}

void Matrix4x4::SetTranslation(Vec3 v) {
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15
	*/
	buff[3] = v.x;
	buff[7] = v.y;
	buff[11] = v.z;
}
void Matrix4x4::SetScale(Vec3 s) {
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15
	*/
	buff[0] = s.x; 
	buff[5] = s.y;
	buff[10] = s.z;
}
Matrix4x4 Matrix4x4 ::Ortho(float left, float right, float bot, float top, float near, float far) {
	Matrix4x4 m;
	m.buff[0] = 2 / (right - left);
	m.buff[5] = 2 / (top - bot);
	m.buff[10] = -2 / (far - near);

	m.buff[3] = -(right + left) / (right - left);
	m.buff[7] = -(top + bot)/ (top - bot);
	m.buff[11] = -(far + near)/(far - near);
	return m;
}
void Matrix4x4::SetRotation(float ang) {
	buff[0] = cos(ang);
	buff[1] = -sin(ang);
	buff[4] = sin(ang);
	buff[5] = cos(ang);
}
Matrix4x4 Matrix4x4::RotationMatrix(float ang) {
	Matrix4x4 m(1.0f);
	m.SetRotation(ang);
	return m;
}
Matrix4x4 Matrix4x4::ScaleMatrix(Vec3 scale) {
	Matrix4x4 m(1.0f);
	m.SetScale(scale);
	return m;
}
Matrix4x4 Matrix4x4::TranslationMatrix(Vec3 pos) {
	Matrix4x4 m(1.0f);
	m.SetTranslation(pos);
	return m;
}
