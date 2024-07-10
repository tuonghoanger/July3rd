#pragma once

#include <math.h>
#include <cmath>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template <typename T>
inline auto sq(const T& x)
{
	return x * x;
}

template<typename T>
inline T wrap_angle(T theta)
{
	const T modded = fmod(theta, (T)2.0 * (T)PI_D);
	return (modded > (T)PI_D) ?
		(modded - (T)2.0 * (T)PI_D) :
		modded;	// -pi to pi
}

template<typename T>
inline T interpolate(const T& src, const T& dst, float alpha)
{
	return src + (dst - src) * alpha;
}