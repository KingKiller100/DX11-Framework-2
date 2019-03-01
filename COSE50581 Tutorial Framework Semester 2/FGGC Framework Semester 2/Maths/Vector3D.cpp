#include "Vector3.h"

Vector3D::Vector3D(const float x, const float y, const float z) : x(x), y(y), z(z) {/*Empty*/}

Vector3D::Vector3D(const float &f)
{
	x = y = z = f;
}

Vector3D::Vector3D()
{
	x = y = z = 0.f;
}

Vector3D::~Vector3D()
= default;

float Vector3D::Magnitude(const Vector3 &v)
{
	return sqrtf(MagnitudeSQ(v));
}

float Vector3D::MagnitudeSQ(const Vector3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float Vector3D::DotProduct(const Vector3& v, const Vector3& u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

float Vector3D::AngleBetweenVectors(const Vector3& v, const Vector3& u, bool inDegrees)
{
	const float angle = DotProduct(v, u) / (Magnitude(v) * Magnitude(u));
	
	const float toDegrees = 180 / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

Vector3 Vector3D::CrossProduct(const Vector3& u, const Vector3& v)
{
	return Vector3(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

Vector3 Vector3D::Normalize(const Vector3& v)
{
	const float mag = Magnitude(v);	

	return mag == 0 ? v / mag : v;
}

void Vector3D::Zero()
{
	x = y = z = 0;
}

void Vector3D::Truncate(const float max)
{
	if (fabsf(Magnitude(*this)) > max)
	{
		*this = Normalize(*this) * max;
	}
}

Vector3 Vector3D::ReverseVector()
{
	Vector3 vec = *this;

	return vec * -1;
}

float Vector3D::Distance(const Vector3 & v)
{
	/*float xSeperation = v.x - x;
	float ySeperation = v.y - y;
	float zSeperation = v.z - z;*/

	Vector3 vecSeperation = v - (*this);

	return Magnitude(vecSeperation);
}
