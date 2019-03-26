#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <cmath>
#include <complex>

template <class T>
T Vector3<T>::MagnitudeSQ(const Vector3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template <class T>
T Vector3<T>::Magnitude(const Vector3& v)
{
	return std::sqrt(Vector3::MagnitudeSQ(v));
}

template<class T>
T Vector3<T>::DotProduct(const Vector3& v, const Vector3& u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

template<class T>
T Vector3<T>::AngleBetweenVectors(const Vector3& v, const Vector3& u, const bool inDegrees)
{
	const float angle = Vector3::DotProduct(v, u) / (Vector3::Magnitude(v) * Vector3::Magnitude(u));
	
	const float toDegrees = 180.f / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

template<class T>
Vector3<T> Vector3<T>::CrossProduct(const Vector3& u, const Vector3& v)
{
	return Vector3(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

template<class T>
Vector3<T> Vector3<T>::Normalize(const Vector3& v)
{
	const float mag = Vector3::Magnitude(v);

	return mag == 0 ? v / mag : v;
}

template<class T>
void Vector3<T>::Zero()
{
	x = y = z = 0;
}

template<class T>
void Vector3<T>::Truncate(const float max)
{
	if (::fabsf(Vector3::Magnitude(*this)) > max)
	{
		*this = Vector3::Normalize(*this) * max;
	}
}

template<class T>
Vector3<T> Vector3<T>::ReverseVector()
{
	return *this * -1;
}

template <class T>
void Vector3<T>::ToPositives()
{
	x < 0 ? x = ::fabsf(x) : x;
	y < 0 ? y = ::fabsf(y) : y;
	z < 0 ? z = ::fabsf(z) : z;
}

template<class T>
T Vector3<T>::Distance(const Vector3& v)
{
	return Vector3::Magnitude(v - *this);
}
