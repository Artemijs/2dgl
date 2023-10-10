#include "Matrix4x4.h"
#include <iostream>


Vec2::Vec2() {
	x = 0; y = 0;
}
Vec2::Vec2(float mx, float my) {
	x = mx;
	y = my;
}
bool Vec2::operator==(const Vec2& v) const{
	return (v.x == x && v.y == y);
}
void Vec2::operator=(const Vec2& v) {
	x = v.x;
	y = v.y;
}
Vec2 Vec2::operator-(const Vec2& v)const {
	return Vec2(x - v.x, y - v.y);
}
Vec2 Vec2::operator+(const Vec2& v) const{
	return Vec2(x + v.x, y + v.y);
}
Vec2 Vec2::operator*(const float f) const{
	return Vec2(x * f, y * f);
}
Vec2 Vec2::operator/(const float f) const{
	return Vec2(x/f, y/f);
}
void Vec2::operator+=(const Vec2& v) {
	x += v.x;
	y += v.y;
}
const float Vec2::Distance(const Vec2& a, const Vec2& b) {
	return std::sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}
const float Vec2::Distance(const float ax, const float ay, const float bx, const float by) {
	return std::sqrtf(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay)));
}
const float Vec2::Lenght(const Vec2& v) {
	return std::sqrtf((v.x * v.x) + (v.y * v.y));
}
void Vec2::Normalize() {
	(*this) /= Vec2::Lenght((*this));
}
void Vec2::operator/=(const float f) {
	x /= f;
	y /= f;
}
const Vec2 Vec2::Normalize(const Vec2 &v) {
	return v / Vec2::Lenght(v);
}
const float Vec2::Dot(const Vec2& a, const Vec2& b) {
	return (a.x * b.x) + (a.y * b.y);
}
const float Vec2::Dot(const float ax, const float ay, const float bx, const float by) {
	return (ax * bx) + (ay * by);
}
const Vec2 Vec2::LineIntersection(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d) {
	//additive vector form
	Vec2 r = (b - a);
	Vec2 s = (d - c);

	float dd = r.x * s.y - r.y * s.x;
	float u = ((c.x - a.x) * r.y - (c.y * a.y) * r.x) / dd;
	float t = ((c.x - a.x) * s.y - (c.y * a.y) * s.x) / dd;
	if (0 <= u && u <= 1 && 0 <= t && t <= 1) {
		return a + (r*t);
	}
	return Vec2(0, 0);
}




Vec2Int::Vec2Int() {
	x = 0; y = 0;
}
Vec2Int::Vec2Int(int mx, int my) {
	x = mx;
	y = my;
}
bool Vec2Int::operator==(const Vec2Int& v)const {
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
const Vec3 Vec3::operator+(const Vec3& v) const{
	return Vec3(x + v.x, y + v.y, z + v.z);
}
const Vec3 Vec3::operator-(const Vec3& v) const {
	return Vec3(x - v.x, y - v.y, z - v.z);
}
const Vec3 Vec3::operator*(float f) const{
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
void Vec3::operator=(const Vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
const Vec3 Vec3::operator/(const float f) const{
	return Vec3(x / f, y / f, z / f);
}
const bool Vec3::operator==(const Vec3& v) const {
	return (v.x == x && v.y == y && v.z == z);
}
const float Vec3::Lenght() const {
	return std::sqrt((x * x + y * y + z * z));
}

/*const Vec3 Vec3::operator*(const float& lhs, const Vec3& rhs) {

	return Vec3(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}
Vec3 Vec3::operator/(const float& lhs, const Vec3& rhs) {

	return Vec3(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs);
}*/
void Vec3::Normalize() {
	(*this) /= Lenght();
}
const Vec3 Vec3::Normalize( const Vec3& vec){
	return vec/ vec.Lenght();
}
const float Vec3::DistanceTo(const Vec3& other) {
	return Vec3(x - other.x, y - other.y, z - other.z).Lenght();
}
const float Vec3::Distance(const Vec3& a, const Vec3& b) {
	return std::sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)) + ((b.z - a.z) * (b.z - a.z)));
}
const float Vec3::Distance(const float ax, const float ay, const float az, const float bx, const float by, const float bz) {
	return std::sqrtf(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay)) + ((bz - az) * (bz - az)));
}
const float Vec3::Lenght(const Vec3& v) {
	return std::sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
}

//a * b = x(aybz - azby) + y(azbx - axbz) +z(axby - aybx)
Vec3 Vec3::Cross(const Vec3& a, const Vec3& b) {
	/*
		ay* bz - az * b.y,
		az* b.x - ax * b.z,
		ax* b.y - ay * b.x
	*/
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float Vec3::Dot(const Vec3& a, const Vec3& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
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


/*
float buff[9] = {   0,0,0,
					0,0,0,
					0,0,0
*/
Matrix3x3::Matrix3x3() {

}
Matrix3x3::Matrix3x3(const Matrix3x3& m) {
	for (int i = 0; i < 9; i++) {
		buff[i] = m.buff[i];
	}
}
Matrix3x3::Matrix3x3(float n) {
	buff[0] = n;
	buff[4] = n;
	buff[8] = n;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m)const {
	Matrix3x3 rm = Matrix3x3();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] + buff[i];
	}
	return rm;
}
Matrix3x3 Matrix3x3::operator-(const Matrix3x3& m)const {
	Matrix3x3 rm = Matrix3x3();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] - buff[i];
	}
	return rm;
}
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m)const {
	Matrix3x3 rm = Matrix3x3();
	/*
	0 1 2
	3 4 5
	6 7 8
	*/
	//r1 x c1 
	rm.buff[0] = buff[0] * m.buff[0] + buff[1] * m.buff[3] + buff[2] * m.buff[6];
	//r2 x c1
	rm.buff[3] = buff[3] * m.buff[0] + buff[4] * m.buff[3] + buff[5] * m.buff[6];
	//r3 x c1
	rm.buff[6] = buff[6] * m.buff[0] + buff[7] * m.buff[3] + buff[8] * m.buff[6];
	

	//r1 x c2 
	rm.buff[0] = buff[0] * m.buff[1] + buff[1] * m.buff[4] + buff[2] * m.buff[7];
	//r2 x c2
	rm.buff[3] = buff[3] * m.buff[1] + buff[4] * m.buff[4] + buff[5] * m.buff[7];
	//r3 x c2
	rm.buff[6] = buff[6] * m.buff[1] + buff[7] * m.buff[4] + buff[8] * m.buff[7];

	//r1 x c3 
	rm.buff[0] = buff[0] * m.buff[2] + buff[1] * m.buff[5] + buff[2] * m.buff[8];
	//r2 x c3
	rm.buff[3] = buff[3] * m.buff[2] + buff[4] * m.buff[5] + buff[5] * m.buff[8];
	//r3 x c3
	rm.buff[6] = buff[6] * m.buff[2] + buff[7] * m.buff[5] + buff[8] * m.buff[8];

	return rm;
}
	
Vec3 Matrix3x3::operator*(const Vec3& v) {
	Vec3 v3 = Vec3();
	v3.x = buff[0] * v.x + buff[1] * v.y + buff[2] * v.z;
	//r2 x c1
	v3.y = buff[3] * v.x + buff[4] * v.y + buff[5] * v.z;
	//r3 x c1
	v3.z = buff[6] * v.x + buff[7] * v.y + buff[8] * v.z;

	return v3;
}
const Vec3 Matrix3x3::operator*(const Vec3& v)const {
	Vec3 v3 = Vec3();
	v3.x = buff[0] * v.x + buff[1] * v.y + buff[2] * v.z;
	//r2 x c1
	v3.y = buff[3] * v.x + buff[4] * v.y + buff[5] * v.z;
	//r3 x c1
	v3.z = buff[6] * v.x + buff[7] * v.y + buff[8] * v.z;

	return v3;
}
//};

Matrix3x3 Matrix3x3::RotationMatrix(const float rotation, const Vec3& axis) {
	//this needs to be a 3x3 matrix		
	Matrix3x3 m = Matrix3x3(1.0f);		
	const float cosA = cosf(rotation);
	const float sinA = sinf(rotation);

	m.buff[0] = cosA + pow(axis.x, 2) * (1 - cosA);
	m.buff[1] = axis.x * axis.y * (1 - cosA) - axis.z * sinA;
	m.buff[2] = axis.x * axis.z * (1 - cosA) + axis.y * sinA;
										
	m.buff[3] = axis.y * axis.x * (1 - cosA) + axis.z * sinA;
	m.buff[4] = cosA + pow(axis.y, 2) * (1 - cosA);
	m.buff[5] = axis.y * axis.z * (1 - cosA) - axis.x * sinA;

	m.buff[6] = axis.z * axis.x * (1 - cosA) - axis.y * sinA;
	m.buff[7] = axis.z * axis.y * (1 - cosA) + axis.x * sinA;
	m.buff[8] = cosA + pow(axis.z, 2) * (1 - cosA);

	return m;
}









Matrix4x4::Matrix4x4(const Matrix4x4& m) {
	for (int i = 0; i < 16; i++) {
		buff[i] = m.buff[i];
	}
}
Matrix4x4::Matrix4x4() {
}
Matrix4x4::Matrix4x4(float n) {
	buff[0] = n;
	buff[5] = n;
	buff[10] = n;
	/*
	0 1 2 3
	4 5 6 7
	8 9 10 11
	0 0 0 1
	*/	
}
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m)const  {
	Matrix4x4 rm = Matrix4x4();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] + buff[i];
	}
	return rm;
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& m) const {
	Matrix4x4 rm = Matrix4x4();
	for (int i = 0; i < 16; ++i) {
		rm.buff[i] = m.buff[i] - buff[i];
	}
	return rm;
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) const {
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

Vec3 Matrix4x4::operator* (const Vec3& v) {
	Vec3 v3 = Vec3();
	v3.x = buff[0] * v.x + buff[1] * v.y + buff[2] * v.z + buff[3] * 1;
	//r2 x c1
	v3.y = buff[4] * v.x + buff[5] * v.y + buff[6] * v.z + buff[7] * 1;
	//r3 x c1
	v3.z = buff[8] * v.x + buff[9] * v.y + buff[10] * v.z + buff[11] * 1;
	//r4 x c1
	return v3;
}
const Vec3 Matrix4x4::operator* (const Vec3& v) const {
	Vec3 v3 = Vec3();
	v3.x = buff[0] * v.x + buff[1] * v.y + buff[2] * v.z + buff[3] * 1;
	//r2 x c1
	v3.y = buff[4] * v.x + buff[5] * v.y + buff[6] * v.z + buff[7] * 1;
	//r3 x c1
	v3.z = buff[8] * v.x + buff[9] * v.y + buff[10] * v.z + buff[11] * 1;
	//r4 x c1
	return v3;
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
/// <summary>
/// this only works for one axis at the moment
/// </summary>
/// <param name="ang"></param>
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
//float GetAngle();
Vec3 Matrix4x4::GetPosition() const {
	return Vec3(buff[3], buff[7], buff[11]);
}
Vec3 Matrix4x4::GetSize() const {
	return Vec3(buff[0], buff[5], buff[10]);
}
Matrix4x4 Matrix4x4::GetMatrix(Vec3 pos, Vec3 scale, float ang) {
	
	//tsr
	return Matrix4x4::TranslationMatrix(pos) * Matrix4x4::ScaleMatrix(scale) * Matrix4x4::RotationMatrix(ang);
}
/// <summary>
/// 3d camera perspective
/// </summary>
/// <param name="fov">in radians</param>
/// <param name="aspect">width/height</param>
/// <param name="near">0.1f, cant be 0 for mathematical reasons</param>
/// <param name="far"> </param>
/// <returns></returns>
Matrix4x4 Matrix4x4::Perspective(const float fov, const float aspect, const float near, const float far) {
	Matrix4x4 m;
	m.buff[0] = 1 / (aspect * std::tanf(fov / 2));
	m.buff[5] = 1 / (std::tanf(fov / 2));
	m.buff[10] = -((far + near) / (far - near));
	m.buff[11] = -((2 * far * near) / (far - near));
	m.buff[14] = -1;
	return m;
}
Matrix4x4 Matrix4x4::GetCameraMatrix(const Vec3& X, const Vec3& Y, const Vec3& Z, const Vec3& O) {
	Matrix4x4 m(1.0f);
	//0  1  2  3
	//4  5  6  7
	//8  9  10 11
	//12 13 14 15
	

	m.buff[0] = X.x;
	m.buff[1] = X.y;
	m.buff[2] = X.z;
	//1 5 9  y
	m.buff[4] = Y.x;
	m.buff[5] = Y.y;
	m.buff[6] = Y.z;
	//2 6 10 z
	m.buff[8] = Z.x;
	m.buff[9] = Z.y;
	m.buff[10] = Z.z; 

	//0 4 8  X
	/*m.buff[0] = X.x;
	m.buff[4] = X.y;
	m.buff[8] = X.z;
	//1 5 9  y
	m.buff[1] = Y.x;
	m.buff[5] = Y.y;
	m.buff[9] = Y.z;
	//2 6 10 z
	m.buff[2] = Z.x;
	m.buff[6] = Z.y;
	m.buff[10] = Z.z;*/
	//3 7 11 O
	/*m.buff[3] = O.x;
	m.buff[7] = O.y;
	m.buff[11] = O.z;
	*/
	m.buff[15] = 1.0f;
	Matrix4x4 m1(1.0f);
	m1.SetTranslation(O *-1);

	return m * m1;
}

Matrix4x4 Matrix4x4::RotationMatrix(const float rotation, const Vec3& axis) {
	//this needs to be a 3x3 matrix		
	Matrix4x4 m = Matrix4x4(1.0f);
	const float cosA = cosf(rotation);
	const float sinA = sinf(rotation);

	m.buff[0] = cosA + pow(axis.x, 2) * (1 - cosA);
	m.buff[1] = axis.x * axis.y * (1 - cosA) - axis.z * sinA;
	m.buff[2] = axis.x * axis.z * (1 - cosA) + axis.y * sinA;

	m.buff[3] = axis.y * axis.x * (1 - cosA) + axis.z * sinA;
	m.buff[4] = cosA + pow(axis.y, 2) * (1 - cosA);
	m.buff[5] = axis.y * axis.z * (1 - cosA) - axis.x * sinA;

	m.buff[6] = axis.z * axis.x * (1 - cosA) - axis.y * sinA;
	m.buff[7] = axis.z * axis.y * (1 - cosA) + axis.x * sinA;
	m.buff[8] = cosA + pow(axis.z, 2) * (1 - cosA);
	return m;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//										RAY
///////////////////////////////////////////////////////////////////////////////////////////////


Ray::Ray() :_distance(0), _direction(Vec3()){
}


Ray::Ray(float dist, Vec3 dir) : _distance(dist), _direction(dir) {

}

Ray::~Ray() {
	
}