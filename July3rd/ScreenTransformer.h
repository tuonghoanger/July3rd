#pragma once

#include "Graphics.h"
#include "Vec3.h"

class ScreenTransformer	// transform from -1,1 to ScreenWidth , ScreenHeight (top left screen is 0,0 )
{
public:
	ScreenTransformer()
		:
		xFactor(float(Graphics::ScreenWidth) / 2.0f),
		yFactor(float(Graphics::ScreenHeight) / 2.0f)
	{}
	Vec3& Transform(Vec3& v) const
	{
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor;
		return v;
	}
	Vec3 GetTransformed(const Vec3& v) const
	{
		Vec3 n = v;
		return Transform(n);
	}
private:
	float xFactor;
	float yFactor;
};