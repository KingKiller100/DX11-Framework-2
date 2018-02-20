#pragma once
#include <math.h>

struct Vector3D
{
	float x, y, z;

	Vector3D();

	Vector3D(float x, float y, float z);

	~Vector3D();

	static float GetMagnitude(const Vector3D v);

	// Produces the dot product
	static float DotProduct(const Vector3D v, const Vector3D u);

	// Finds angle between two vectors in degrees/radians
	static float AngleBetweenV3D(const Vector3D v, const Vector3D u, bool rads);

	// Outputs the normal between two vectors
	static Vector3D CrossProduct(const Vector3D& u, const Vector3D& v);

	// Normalizes a vector
	void Normalize();

	// Overloads + operator to add two vectors objects
	Vector3D operator+(const Vector3D& v) const
	{
		return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	// Overloads - operator to subtract two vectors objects
	Vector3D operator-(const Vector3D& v) const
	{
		return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	// Overloads * operator to multiply a vector and float object
	Vector3D operator*(const float& v) const
	{
		return Vector3D(this->x * v, this->y * v, this->z * v);
	}

	// Overloads * operator to multiply two vector objects
	Vector3D operator*(const Vector3D& v) const
	{
		return Vector3D(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	// Overloads / operator to divide a vector and float object
	Vector3D operator/(const float& v) const
	{
		return Vector3D(this->x / v, this->y / v, this->z / v);
	}

	// Overloads / operator to divide two vectors objects
	Vector3D operator/(const Vector3D& v) const
	{
		return Vector3D(this->x / v.x, this->y / v.y, this->z / v.z);
	}

	// Overloads = operator to make one vector axis values equal to another
	Vector3D operator=(const Vector3D& v)
	{
		return Vector3D(this->x = v.x, this->y = v.y, this->z = v.z);
	}

	// bool operator == returns true if both Vector3D values are equal
	bool operator==(const Vector3D& v) const
	{
		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}

	// bool operator != returns true if both Vector3D values are NOT equal
	bool operator!=(const Vector3D& v)
	{
		return !(this->x == v.x && this->y == v.y && this->z == v.z);
	}

	Vector3D& operator+=(const Vector3D& v)
	{
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		this->z = this->z + v.z;

		return *this;
	}
};

