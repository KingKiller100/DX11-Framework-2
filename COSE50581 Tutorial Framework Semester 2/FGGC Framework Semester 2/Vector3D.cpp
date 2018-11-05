#include "Vector3D.h"

Vector3D::Vector3D(const float x, const float y, const float z) : x(x), y(y), z(z) {/*Empty*/}

Vector3D::Vector3D(const float &f)
{
	x = y = z = f;
}

Vector3D::Vector3D()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3D::~Vector3D()
{
}

float Vector3D::GetMagnitude(const Vector3D v)
{
	return sqrtf(powf(v.x, 2) + powf(v.y, 2) + pow(v.z, 2));
}

float Vector3D::DotProduct(const Vector3D v, const Vector3D u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

float Vector3D::AngleBetweenV3D(const Vector3D v, const Vector3D u, bool inRadians)
{
	float angle = DotProduct(v, u);
	angle /= (GetMagnitude(v) * GetMagnitude(u));
	
	//const float pi = 2 * acosf(0.0f);
	const float toRadians = M_PI / 180;

	if (inRadians)
	{
		//Converts angle to radians 
		return angle = acosf(angle) * toRadians;
	}
		
	return angle = acosf(angle);
}

Vector3D Vector3D::CrossProduct(const Vector3D& u, const Vector3D& v)
{
	return Vector3D(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

Vector3D Vector3D::Normalize(Vector3D v)
{
	float mag = GetMagnitude(v);

	if (mag == 0)
	{
		return v;
	}

	v /= mag;

	return v;
}

void Vector3D::Zero()
{
	x = y = z = 0;
}

void Vector3D::Truncate(float max)
{
	if (fabsf(GetMagnitude(*this)) > max)
	{
		*this = Normalize(*this) * max;
	}
}

Vector3D Vector3D::ReverseVector()
{
	Vector3D vec = *this;

	return vec * -1;
}

float Vector3D::Distance(const Vector3D & v)
{
	/*float xSeperation = v.x - x;
	float ySeperation = v.y - y;
	float zSeperation = v.z - z;*/

	Vector3D vecSeperation = v - (*this);

	return GetMagnitude(vecSeperation);
}
