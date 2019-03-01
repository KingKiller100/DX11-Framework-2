#pragma once

#include <math.h>

#define _USE_MATH_DEFINES
#include <cmath>

template<class precision>
struct Vector3
{
	float x, y, z;

	Vector3();
	Vector3(const float x, const float y, const float z);
	Vector3(const float &f);

	~Vector3();

	static float Magnitude(const Vector3& v);

	static float MagnitudeSQ(const Vector3& v);
		
	// Produces the dot product
	static float DotProduct(const Vector3& v, const Vector3& u);

	// Finds angle between two vectors in degrees/radians
	static float AngleBetweenVectors(const Vector3& v, const Vector3& u, bool inDegrees);

	// Outputs the normal between two vectors
	static Vector3 CrossProduct(const Vector3& u, const Vector3& v);

	// Normalizes a vector
	static Vector3 Normalize(const Vector3& v);

	// Sets all values of the vector to zero
	void Zero();

	void Truncate(const float max);

	Vector3 ReverseVector();

	// Calculates distance between two 3D objects
	float Distance(const Vector3 &v);

	// Overloads + operator to add two vectors objects
	Vector3 operator+(const Vector3& v) const													{ return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }

	// Overloads - operator to subtract two vectors objects
	Vector3 operator-(const Vector3& v) const													{ return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }

	// Overloads * operator to multiply a vector and float object
	Vector3 operator*(const float& f) const													{ return Vector3(this->x * f, this->y * f, this->z * f); }

	// Overloads * operator to multiply two vector objects
	Vector3 operator*(const Vector3& v) const													{ return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }

	// Overloads / operator to divide a vector and float object
	Vector3 operator/(const float& f) const													{ return Vector3(this->x / f, this->y / f, this->z / f); }
	
	// Overloads / operator to divide two vectors objects
	Vector3 operator/(const Vector3& v) const													{ return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

	// Overloads = operator to make one vector axis values equal to another
	Vector3 operator=(const Vector3& v)														{ return Vector3(this->x = v.x, this->y = v.y, this->z = v.z); }

	// bool operator == returns true if both Vector3D values are equal
	bool operator==(const Vector3& v) const													{ return (this->x == v.x && this->y == v.y && this->z == v.z); }

	// bool operator != returns true if both Vector3D values are NOT equal
	bool operator!=(const Vector3& v) const													{ return !(*this == v); }

	// adds to current vector3d value
	Vector3& operator+=(const Vector3& v)
	{
		*this = *this + v;

		return *this;
	}

	// divides current vector3d value
	Vector3& operator-=(const Vector3& v)
	{
		*this = *this - v;

		return *this;
	}

	// divides current vector3d value and sets variable to it
	Vector3& operator/=(const Vector3& v)
	{
		*this = *this / v;

		return *this;
	}

	// divides current vector3d value by a float and sets variable to it
	Vector3& operator/=(const float& f)
	{
		*this = *this / f;

		return *this;
	}

	// multiplies current vector3d value and sets variable to it
	Vector3& operator*=(const Vector3& v)
	{
		*this = *this * v;

		return *this;
	}

	// multiply current vector3d value by a float and sets variable to it
	Vector3& operator*=(const float& f)
	{
		*this = *this * f;

		return *this;
	}
};

