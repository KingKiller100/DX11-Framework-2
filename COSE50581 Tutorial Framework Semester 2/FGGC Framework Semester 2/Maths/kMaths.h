#pragma once
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include <algorithm>
#include <corecrt_math_defines.h>

typedef  Vector3<int>		Vector3i;
typedef  Vector3<float>		Vector3f;
typedef  Vector3<double>	Vector3d;
typedef  Vector3<unsigned>	Vector3u;

#define TAU (M_PI * 2)

template<class TypePrecision>
TypePrecision RadiansToDegrees(const TypePrecision radians)															{ return radians * std::forward<TypePrecision>(360.0 / TAU); }

template<class TypePrecision>
TypePrecision DegreesToRadians(const TypePrecision degrees)															{ return degrees * std::forward<TypePrecision>(TAU / 360.f); }

template<class TypePrecision>
TypePrecision Clamp(const TypePrecision value, const TypePrecision min, const TypePrecision max)					{ return std::forward<TypePrecision>(std::min(std::max(value, min), max)); }

template<class TypePrecision>
TypePrecision AbsClamp(const TypePrecision value, const TypePrecision min, const TypePrecision max)					{ return value >= 0 ? Clamp(value, min, max) : -Clamp(value, min, max); }
