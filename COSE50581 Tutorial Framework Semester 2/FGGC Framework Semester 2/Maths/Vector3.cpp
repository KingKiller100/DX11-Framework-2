#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <cmath>

template<class T>
Vector3<T>::Vector3(const T x, const T y, const T z) : x(x), y(y), z(z)
{ /*Empty*/ }

template<class T>
Vector3<T>::Vector3(const T f)
{
	x = y = z = f;
}

template<class T>
Vector3<T>::Vector3()
{
	x = y = z = 0.f;
}

template<class T>
Vector3<T>::~Vector3()
= default;

template <class T>
T Vector3<T>::MagnitudeSQ(const Vector3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template<class T>
T Vector3<T>::Magnitude(const Vector3 &v)
{
	return sqrtf(MagnitudeSQ(v));
}

template<class T>
T Vector3<T>::DotProduct(const Vector3& v, const Vector3& u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

template<class T>
T Vector3<T>::AngleBetweenVectors(const Vector3& v, const Vector3& u, const bool inDegrees)
{
	const float angle = DotProduct(v, u) / (Magnitude(v) * Magnitude(u));
	
	const float toDegrees = 180.f / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

template<class T>
Vector3<T> Vector3<T>::CrossProduct(const Vector3& u, const Vector3& v)
{
	return Vector3<T>(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

template<class T>
Vector3<T> Vector3<T>::Normalize(const Vector3& v)
{
	const float mag = Magnitude(v);	

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
	if (fabsf(Magnitude(*this)) > max)
	{
		*this = Normalize(*this) * max;
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
	x < 0 ? x = fabsf(x) : x;
	y < 0 ? y = fabsf(y) : y;
	z < 0 ? z = fabsf(z) : z;
}

template<class T>
T Vector3<T>::Distance(const Vector3& v)
{
	return Magnitude(v - *this);
}
