#include "Vector3.h"

template<class precision>
Vector3<precision>::Vector3(const precision x, const precision y, const precision z) : x(x), y(y), z(z) {/*Empty*/}

template<class precision>
Vector3<precision>::Vector3(const precision &f)
{
	x = y = z = f;
}

template<class precision>
Vector3<precision>::Vector3()
{
	x = y = z = 0.f;
}

template<class precision>
Vector3<precision>::~Vector3()
= default;

template<class precision>
precision Vector3<precision>::MagnitudeSQ(const Vector3<precision>& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template<class precision>
precision Vector3<precision>::Magnitude(const Vector3<precision> &v)
{
	return sqrtf(MagnitudeSQ(v));
}

template<class precision>
precision Vector3<precision>::DotProduct(const Vector3<precision>& v, const Vector3<precision>& u)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

template<class precision>
precision Vector3<precision>::AngleBetweenVectors(const Vector3<precision>& v, const Vector3<precision>& u, bool inDegrees)
{
	const float angle = DotProduct(v, u) / (Magnitude(v) * Magnitude(u));
	
	const float toDegrees = 180 / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

template<class precision>
Vector3<precision> Vector3<precision>::CrossProduct(const Vector3<precision>& u, const Vector3<precision>& v)
{
	return Vector3<precision>(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

template<class precision>
Vector3<precision> Vector3<precision>::Normalize(const Vector3<precision>& v)
{
	const float mag = Magnitude(v);	

	return mag == 0 ? v / mag : v;
}

template<class precision>
void Vector3<precision>::Zero()
{
	x = y = z = 0;
}

template<class precision>
void Vector3<precision>::Truncate(const float max)
{
	if (fabsf(Magnitude(*this)) > max)
	{
		*this = Normalize(*this) * max;
	}
}

template<class precision>
Vector3<precision> Vector3<precision>::ReverseVector()
{
	Vector3<precision> vec = *this;

	return vec * -1;
}

template <class precision>
void Vector3<precision>::ToPositives()
{
	if (x < 0) x = fabsf(x);
	if (y < 0) y = fabsf(y);
	if (z < 0) z = fabsf(z);
}

template<class precision>
precision Vector3<precision>::Distance(const Vector3 & v)
{
	return Magnitude(v - *this);
}
