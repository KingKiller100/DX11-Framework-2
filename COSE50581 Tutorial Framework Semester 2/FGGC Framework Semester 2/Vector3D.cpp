#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3D::~Vector3D()
{
//	delete this;
}

float Vector3D::GetMagnitude(const Vector3D v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float Vector3D::DotProduct(const Vector3D v, const Vector3D u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

float Vector3D::AngleBetweenV3D(const Vector3D v, const Vector3D u, bool isRadians)
{
	float angle = DotProduct(v, u);
	angle /= (GetMagnitude(v) * GetMagnitude(u));

	const float pi = 2 * acosf(0.0f);
	const float toRadians = pi / 180;
	if (isRadians == true)
	{
		//Converts angle to radians then creates 
		return angle = acosf(angle) * toRadians;
	}
	else
	{
		return angle = acosf(angle);
	}
}

Vector3D Vector3D::CrossProduct(const Vector3D& u, const Vector3D& v)
{
	return Vector3D(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

void Vector3D::Normalize()
{
	float mag = GetMagnitude(Vector3D(this->x, this->y, this->z));

	this->x = this->x / mag;
	this->y = this->y / mag;
	this->z = this->z / mag;
}
