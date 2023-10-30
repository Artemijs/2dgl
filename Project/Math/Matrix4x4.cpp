#include "Matrix4x4.h"
#include <iostream>
#include "../Util/Utility.h"



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

	m.buff[0] = cosA + pow(axis.x, 2.0f) * (1.0f - cosA);
	m.buff[1] = axis.x * axis.y * (1.0f - cosA) - axis.z * sinA;
	m.buff[2] = axis.x * axis.z * (1.0f - cosA) + axis.y * sinA;
										
	m.buff[3] = axis.y * axis.x * (1.0f - cosA) + axis.z * sinA;
	m.buff[4] = cosA + pow(axis.y, 2.0f) * (1.0f - cosA);
	m.buff[5] = axis.y * axis.z * (1.0f - cosA) - axis.x * sinA;

	m.buff[6] = axis.z * axis.x * (1.0f - cosA) - axis.y * sinA;
	m.buff[7] = axis.z * axis.y * (1.0f - cosA) + axis.x * sinA;
	m.buff[8] = cosA + pow(axis.z, 2.0f) * (1.0f - cosA);

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


Matrix4x4 Matrix4x4::Inverse()  {

	Matrix4x4 inverse = Matrix4x4(1.0f);
	Matrix4x4 mat = Matrix4x4((*this));
	/*
		pivot elements
		1000	0
		0100	5	(4 + 1)	
		0010	10	(8 + 2)
		0001	15	(12+ 3)
		pivot element = rowi + colj
	*/

	// Loop through each column of the matrix
	for (int i = 0; i < 4; i++) {

		// Find the pivot element
		float pivot = mat.buff[i * 5];
		int pivot_row = i;

		//find the smallest pivot?
		for (int j = i + 1; j < 4; j++) {
			//j = next column
			//buff[j][i] = pivot of the next row
			if (abs(mat.buff[j * 5]) > abs(pivot)) {
				pivot = mat.buff[j * 5];
				pivot_row = j;
			}
		}

		// Swap the rows if necessary
		if (pivot_row != i) {
			//to swap 2 rows in a 1d array i have to find the start and end of each row
			//rowA = i*4, len 4
			//rowB = ( i + 1 ) * 4, len 4
			Utility::Swap(mat.buff, i * 4, (i + 1) * 4, 4);
		}

		// Divide the row by the pivot element
		float divisor = mat.buff[i * 5];
		for (int j = 0; j < 4; j++) {
			mat.buff[i * 4 + j] /= divisor;
			inverse.buff[i * 4 + j] /= divisor;
		}

		// Subtract the row from the other rows to create zeros
		for (int j = 0; j < 4; j++) {//j is the row i is the column
			//go through each row
			if (j != i) {//if the row is not equal to the pivot row
				float factor = mat.buff[j * 4 + i];//[row][col] row = j*4 col = i

				for (int k = 0; k < 4; k++) {
					//i = 
					//matrix[i][k] 
					// 
					//buff[row][col] -= factor buff[row][col]
					mat.buff[j * 4 + k] -= factor * mat.buff[i * 4 + k];
					//inverse[row][col] -= factor inverse[row][col]
					inverse.buff[j * 4 + k] -= factor * inverse.buff[i * 4 + k];
				}
			}
		}
		
	}

	return inverse;

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

	//r(xAng, yAng, zAng) = m; 
	//xAng = atan2(r 3-2, r 3-3);
	//zAng = atan2(r 2-1, r 1-1);
	//yAng ={
	//	if(cos(zAng) == 0
	//			atan2(-r3-1, r2-1/sin(zAng))
	// else
	//			atan2(-r3-1, r1-1/sin(zAng))
	//}

}

Matrix4x4 Matrix4x4::RotationMatrixX(float ang) {
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15
	*/
	Matrix4x4 m(1.0f);
	if (ang == 0) return m;

	m.buff[5] = cos(ang);
	m.buff[6] = -sin(ang);
	m.buff[9] = sin(ang);
	m.buff[10] = cos(ang);

	return m;
}


Matrix4x4 Matrix4x4::RotationMatrixY(float ang) {
	Matrix4x4 m(1.0f);
	if (ang == 0) return m;
	m.buff[0] = cos(ang);
	m.buff[2] = sin(ang);
	m.buff[8] = -sin(ang);
	m.buff[10] = cos(ang);

	return m;
}


Matrix4x4 Matrix4x4::RotationMatrixZ(float ang) {
	Matrix4x4 m(1.0f);
	if (ang == 0) return m;
	m.buff[0] = cos(ang);
	m.buff[1] = -sin(ang);
	m.buff[4] = sin(ang);
	m.buff[5] = cos(ang);

	return m;
}


Matrix4x4 Matrix4x4::RotationMatrix(const Vec3& angles) {
	return   RotationMatrixZ(angles.z) * RotationMatrixY(angles.y) * RotationMatrixX(angles.x);
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




//													VEC3
//-----------------------------------------------------------------------------------------

//float GetAngle();
Vec3 Matrix4x4::GetPosition() const {
	return Vec3(buff[3], buff[7], buff[11]);
}


Vec3 Matrix4x4::GetSize() const {
	return Vec3(buff[0], buff[5], buff[10]);
}


Matrix4x4 Matrix4x4::GetMatrix(Vec3 pos, Vec3 scale, Vec3 angles) {
	
	//tsr
	return Matrix4x4::TranslationMatrix(pos) * Matrix4x4::ScaleMatrix(scale) * Matrix4x4::RotationMatrix(angles);
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

	m.buff[15] = 1.0f;
	Matrix4x4 m1(1.0f);
	m1.SetTranslation(O *-1);

	return m * m1;
}


Matrix4x4 Matrix4x4::RotationMatrix(const float rotation, const Vec3& axis) {
	
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

/*
	matrix equivelant rotation
*/
Matrix4x4 Matrix4x4::RotationMatrix(Quaternion q) {
	/*
	* a + bi + cj + dk
	* w + x  + y  +  z
	* 
		2a^2 -1 + 2b^2,		2bc - 2ad,		2bd + 2ac

		2bc + 2ad,		2a^2 - 1 + 2c^2,	2cd - 2ab

		2bd - 2ac,		2cd + 2ab,			2a^2 - 1 + 2d^2

	*/
	Matrix4x4 m = Matrix4x4(1.0f);
	
	m.buff[0] = 2 * std::pow(q._w, 2) - 1 + 2*std::pow(q._x, 2);
	m.buff[1] = 2 * q._x * q._y + 2 * q._w * q._z;
	m.buff[2] = 2 * q._x * q._z - 2 * q._w * q._y;

	m.buff[4] = 2 * q._x * q._y - 2 * q._w * q._z;
	m.buff[5] = 2 * std::pow(q._w, 2) - 1 + 2 * std::pow(q._y, 2);
	m.buff[6] = 2 * q._y * q._z - 2 * q._w * q._y;

	m.buff[8] = 2 * q._x * q._z - 2 * q._w * q._y;
	m.buff[9] = 2 * q._y * q._z + 2 * q._w * q._x;
	m.buff[10] =2 * std::pow(q._w, 2) - 1 + 2 * std::pow(q._z, 2);
	return m;
}








Quaternion Quaternion::FromEulerAngles(const float x, const float y, const float z) {

	float cr = cos(x * 0.5f);
	float sr = sin(x * 0.5f);
	float cp = cos(y * 0.5f);
	float sp = sin(y * 0.5f);
	float cy = cos(z * 0.5f);
	float sy = sin(z * 0.5f);

	//Quaternion q = Quaternion();
	/*q._w = cr * cp * cy + sr * sp * sy;
	q._x = sr * cp * cy - cr * sp * sy;
	q._y = cr * sp * cy + sr * cp * sy;
	q._z = cr * cp * sy - sr * sp * cy;*/
	return Quaternion
	(
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy

	);
}


void Quaternion::SetEulerAngles(const float x, const float y, const float z) {

	float cr = cos(x * 0.5f);
	float sr = sin(x * 0.5f);
	float cp = cos(y * 0.5f);
	float sp = sin(y * 0.5f);
	float cy = cos(z * 0.5f);
	float sy = sin(z * 0.5f);
	
	_w = cr * cp * cy + sr * sp * sy;
	_x = sr * cp * cy - cr * sp * sy;
	_y = cr * sp * cy + sr * cp * sy;
	_z = cr * cp * sy - sr * sp * cy;

}


Vec3 Quaternion::GetEulerAngles() {
	Vec3 v = Vec3();
	// roll (x-axis rotation)
	float sinr_cosp = 2 * (_w * _x + _y * _z);
	float cosr_cosp = 1 - 2 * (_x * _x + _y * _y);
	v.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	float sinp = std::sqrt(1 + 2 * (_w * _y - _x * _z));
	float cosp = std::sqrt(1 - 2 * (_w * _y - _x * _z));
	v.y = 2 * std::atan2(sinp, cosp) - PI / 2;

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (_w * _z + _x * _y);
	float cosy_cosp = 1 - 2 * (_y * _y + _z * _z);
	v.z = std::atan2(siny_cosp, cosy_cosp);

	return v;
}


Quaternion::Quaternion(float x, float y, float z) {
	float cr = cos(x * 0.5);
	float sr = sin(x * 0.5);
	float cp = cos(y * 0.5);
	float sp = sin(y * 0.5);
	float cy = cos(z * 0.5);
	float sy = sin(z * 0.5);

	_w = cr * cp * cy + sr * sp * sy;
	_x = sr * cp * cy - cr * sp * sy;
	_y = cr * sp * cy + sr * cp * sy;
	_z = cr * cp * sy - sr * sp * cy;
}


Quaternion::Quaternion(float Angle, const Vec3& V)
{
	float HalfAngleInRadians = Angle / 2;

	float SineHalfAngle = sinf(HalfAngleInRadians);
	float CosHalfAngle = cosf(HalfAngleInRadians);

	_x = V.x * SineHalfAngle;
	_y = V.y * SineHalfAngle;
	_z = V.z * SineHalfAngle;
	_w = CosHalfAngle;
}


Quaternion::Quaternion(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}


void Quaternion::Normalize()
{
	float Length = sqrtf(_x * _x + _y * _y + _z * _z + _w * _w);

	_x /= Length;
	_y /= Length;
	_z /= Length;
	_w /= Length;
}


Quaternion Quaternion::Conjugate() const
{
	Quaternion ret(_w , -_x, -_y, -_z );
	return ret;
}


Quaternion operator*(const Quaternion& q, const Vec3& v)
{
	float _w = -(q._x * v.x) - (q._y * v.y) - (q._z * v.z);
	float _x = (q._w * v.x) + (q._y * v.z) - (q._z * v.y);
	float _y = (q._w * v.y) + (q._z * v.x) - (q._x * v.z);
	float _z = (q._w * v.z) + (q._x * v.y) - (q._y * v.x);

	Quaternion ret(_w, _x, _y, _z);

	return ret;
}


Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
	float _w = (l._w * r._w) - (l._x * r._x) - (l._y * r._y) - (l._z * r._z);
	float _x = (l._x * r._w) + (l._w * r._x) + (l._y * r._z) - (l._z * r._y);
	float _y = (l._y * r._w) + (l._w * r._y) + (l._z * r._x) - (l._x * r._z);
	float _z = (l._z * r._w) + (l._w * r._z) + (l._x * r._y) - (l._y * r._x);

	Quaternion ret(_w, _x, _y, _z);

	return ret;
}


Vec3 Quaternion::ToDegrees()
{
	Vec3 v = Vec3();

	v.x = Utility::Rad2Deg( atan2(_x * _z + _y * _w, _x * _w - _y * _z));
	v.y  = Utility::Rad2Deg(acos(-_x * _x - _y * _y - _z * _z - _w * _w));
	v.z = Utility::Rad2Deg(atan2(_x * _z - _y * _w, _x * _w + _y * _z));

	return v;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//										RAY
///////////////////////////////////////////////////////////////////////////////////////////////



Ray::Ray() :_distance(0), _direction(Vec3()){
}


Ray::Ray(float dist, Vec3 dir, Vec3 pos) : _distance(dist), _direction(dir), _position(pos) {

}


Ray::~Ray() {
	
}