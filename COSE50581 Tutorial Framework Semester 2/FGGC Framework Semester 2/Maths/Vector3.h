#pragma once
#include <algorithm>

template<class TypePrecision>
struct Vector3 final
{
	TypePrecision x, y, z;

	Vector3();
	Vector3(const TypePrecision x, const TypePrecision y, const TypePrecision z);
	Vector3(const TypePrecision &f);

	~Vector3();

	static TypePrecision Magnitude(const Vector3& v);

	static TypePrecision MagnitudeSQ(const Vector3& v);
		
	// Produces the dot product
	static TypePrecision DotProduct(const Vector3& v, const Vector3& u);

	// Finds angle between two vectors in degrees/radians
	static TypePrecision AngleBetweenVectors(const Vector3& v, const Vector3& u, bool inDegrees = false);

	// Outputs the normal between two vectors
	static Vector3 CrossProduct(const Vector3& u, const Vector3& v);

	// Normalizes a vector
	static Vector3 Normalize(const Vector3& v);

	// Restricts vector value to max value
	void Truncate(const float max);

	// Sets all values of the vector to zero
	void Zero();

	// Returns vector times by -1 - does not resign values
	Vector3 ReverseVector();

	// Reassigns values to be positives
	void ToPositives();

	// Calculates distance between two 3D objects
	TypePrecision Distance(const Vector3 &v);

	// Overloads + operator to add two vectors objects
	Vector3 operator+(const Vector3& v) const													{ return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }

	// Overloads - operator to subtract two vectors objects
	Vector3 operator-(const Vector3& v) const													{ return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }

	// Overloads * operator to multiply a vector and float object
	Vector3 operator*(const TypePrecision& f) const												{ return Vector3(this->x * f, this->y * f, this->z * f); }

	// Overloads * operator to multiply two vector objects
	Vector3 operator*(const Vector3& v) const													{ return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }

	// Overloads / operator to divide a vector and float object
	Vector3 operator/(const TypePrecision& f) const												{ return Vector3(this->x / f, this->y / f, this->z / f); }
	
	// Overloads / operator to divide two vectors objects
	Vector3 operator/(const Vector3& v) const													{ return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

	// Overloads = operator to make one vector axis values equal to another
	Vector3 &operator=(const Vector3& v)														{ return std::move(Vector3(this->x = v.x, this->y = v.y, this->z = v.z)); }
																								
	// bool operator == returns true if both Vector3D values are equal							
	bool operator==(const Vector3& v) const														{ return (this->x == v.x && this->y == v.y && this->z == v.z); }
																								
	// bool operator != returns true if both Vector3D values are NOT equal						
	bool operator!=(const Vector3& v) const														{ return !(*this == v); }

	// adds to current vector3 value
	Vector3& operator+=(const Vector3& v)
	{
		*this = *this + v;

		return *this;
	}

	// divides current vector3 value
	Vector3& operator-=(const Vector3& v)
	{
		*this = *this - v;

		return *this;
	}

	// divides current vector3 value and sets variable to it
	Vector3& operator/=(const Vector3& v)
	{
		*this = *this / v;

		return *this;
	}

	// divides current vector3 value by a float and sets variable to it
	Vector3& operator/=(const TypePrecision& f)
	{
		*this = *this / f;

		return *this;
	}

	// multiplies current vector3 value and sets variable to it
	Vector3& operator*=(const Vector3& v)
	{
		*this = *this * v;

		return *this;
	}

	// multiply current vector3 value by a float and sets variable to it
	Vector3& operator*=(const TypePrecision& f)
	{
		*this = *this * f;

		return *this;
	}
};

