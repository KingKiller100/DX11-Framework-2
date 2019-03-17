#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include <algorithm>
#include <corecrt_math_defines.h>

using Vector3f = Vector3<float>; 
using Vector3d = Vector3<double>; 
using Vector3u = Vector3<unsigned>;

#define TAU (M_PI * 2)

template<class TypePrecision>
TypePrecision RadiansToDegrees(const TypePrecision radians)															{ return radians * std::forward<TypePrecision>(360.0 / TAU); }

template<class TypePrecision>
TypePrecision DegreesToRadians(const TypePrecision degrees)															{ return degrees * std::forward<TypePrecision>(TAU / 360.f); }

template<class TypePrecision>
TypePrecision Clamp(const TypePrecision value, const TypePrecision min, const TypePrecision max)					{ return std::forward<TypePrecision>(std::min(std::max(value, min), max)); }