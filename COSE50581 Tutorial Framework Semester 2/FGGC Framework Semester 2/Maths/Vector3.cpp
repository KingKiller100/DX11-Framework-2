#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <cmath>

template<class TypePrecision>
Vector3<TypePrecision>::Vector3(const TypePrecision x, const TypePrecision y, const TypePrecision z) : x(x), y(y), z(z) {/*Empty*/}

template<class TypePrecision>
Vector3<TypePrecision>::Vector3(const TypePrecision &f)
{
	x = y = z = f;
}

template<class TypePrecision>
Vector3<TypePrecision>::Vector3()
{
	x = y = z = 0.f;
}

template<class TypePrecision>
Vector3<TypePrecision>::~Vector3()
= default;

template<class TypePrecision>
TypePrecision Vector3<TypePrecision>::MagnitudeSQ(const Vector3<TypePrecision>& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template<class TypePrecision>
TypePrecision Vector3<TypePrecision>::Magnitude(const Vector3<TypePrecision> &v)
{
	return sqrtf(MagnitudeSQ(v));
}

template<class TypePrecision>
TypePrecision Vector3<TypePrecision>::DotProduct(const Vector3<TypePrecision>& v, const Vector3<TypePrecision>& u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

template<class TypePrecision>
TypePrecision Vector3<TypePrecision>::AngleBetweenVectors(const Vector3<TypePrecision>& v, const Vector3<TypePrecision>& u, bool inDegrees)
{
	const float angle = DotProduct(v, u) / (Magnitude(v) * Magnitude(u));
	
	const float toDegrees = 180 / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

template<class TypePrecision>
Vector3<TypePrecision> Vector3<TypePrecision>::CrossProduct(const Vector3<TypePrecision>& u, const Vector3<TypePrecision>& v)
{
	return Vector3<TypePrecision>(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

template<class TypePrecision>
Vector3<TypePrecision> Vector3<TypePrecision>::Normalize(const Vector3<TypePrecision>& v)
{
	const float mag = Magnitude(v);	

	return mag == 0 ? v / mag : v;
}

template<class TypePrecision>
void Vector3<TypePrecision>::Zero()
{
	x = y = z = 0;
}

template<class TypePrecision>
void Vector3<TypePrecision>::Truncate(const float max)
{
	if (fabsf(Magnitude(*this)) > max)
	{
		*this = Normalize(*this) * max;
	}
}

template<class TypePrecision>
Vector3<TypePrecision> Vector3<TypePrecision>::ReverseVector()
{
	Vector3<TypePrecision> vec = *this;

	return vec * -1;
}

template <class TypePrecision>
void Vector3<TypePrecision>::ToPositives()
{
	x < 0 ? x = fabsf(x) : x;
	y < 0 ? y = fabsf(y) : y;
	z < 0 ? z = fabsf(z) : z;
}

template<class TypePrecision>
TypePrecision Vector3<TypePrecision>::Distance(const Vector3 & v)
{
	return Magnitude(v - *this);
}
