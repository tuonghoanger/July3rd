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
	template<class Vertex>
	Vertex& Transform(Vertex& v) const
	{
		// perform homo -> ndc on xyz / perspective-correct interpolative divide on all other attributes
		const float wInv = 1.0f / v.pos.w;
		v *= wInv;
		// additional divide for mapped z because it must be interpolated
		// adjust position x,y from perspective normalized space
		// to screen dimension space after perspective divide
		v.pos.x = (v.pos.x + 1.0f) * xFactor;
		v.pos.y = (-v.pos.y + 1.0f) * yFactor;
		// store 1/w in w (we will need the interpolated 1/w
		// so that we can recover the attributes after interp.)
		v.pos.w = wInv;
		return v;
	}
	template<class Vertex>
	Vec3 GetTransformed(const Vertex& v) const
	{
		Vertex n = v;
		return Transform(n);
	}
private:
	float xFactor;
	float yFactor;
};