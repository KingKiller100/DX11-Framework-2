#pragma once
#include "Vector3.h"
#include <algorithm>

using Vector3f = Vector3<float>; 
using Vector3d = Vector3<double>; 
using Vector3u = Vector3<unsigned>;

#define TAU (M_PI * 2)

template<class precision>
precision RadiansToDegrees(const precision radians)													{ return radians * (360.f / TAU); }

template<class precision>
precision DegreesToRadians(const precision degrees)													{ return degrees * (TAU / 360.f); }

template<class precision>
precision Clamp(const precision value, const precision min, const precision max)					{ return std::min(std::max(value, min), max); }