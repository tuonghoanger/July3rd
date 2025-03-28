#pragma once

#include "Vec2.h";

template <typename T>
class _Vec3 : public _Vec2<T>
{
public:
	_Vec3() = default;
	_Vec3(T x, T y, T z)
		:
		_Vec2<T>(x, y),
		z(z)
	{}
	_Vec3(const _Vec3& vect)
		:
		_Vec3(vect.x, vect.y, vect.z)
	{}
	template <typename T2>
	explicit operator _Vec3<T2>() const
	{
		return{ (T2) this->x,(T2) this->y,(T2)z };
	}
	T LenSq() const
	{
		return sq(*this);
	}
	T Len() const
	{
		return sqrt(LenSq());
	}
	_Vec3& Normalize()
	{
		const T length = Len();
		this->x /= length;
		this->y /= length;
		z /= length;
		return *this;
	}
	_Vec3	GetNormalized() const
	{
		_Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}
	_Vec3	operator-() const
	{
		return _Vec3(-this->x, -this->y, -z);
	}
	_Vec3& operator=(const _Vec3& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		z = rhs.z;
		return *this;
	}
	_Vec3& operator+=(const _Vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		z += rhs.z;
		return *this;
	}
	_Vec3& operator-=(const _Vec3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	T		operator*(const _Vec3& rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y + z * rhs.z;
	}
	_Vec3 operator+(const _Vec3& rhs) const
	{
		return _Vec3(*this) += rhs;
	}
	_Vec3 operator-(const _Vec3& rhs) const
	{
		return _Vec3(*this) -= rhs;
	}
	_Vec3& operator*=(const T& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		z *= rhs;
		return *this;
	}
	_Vec3 operator*(const T& rhs) const
	{
		return _Vec3(*this) *= rhs;
	}
	_Vec3 operator%(const _Vec3& rhs) const	// cross product
	{
		return _Vec3(
			this->y * rhs.z - this->z * rhs.y,
			this->z * rhs.x - this->x * rhs.z,
			this->x * rhs.y - this->y * rhs.x);
	}
	_Vec3& operator/=(const T& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		z /= rhs;
		return *this;
	}
	_Vec3	operator/(const T& rhs) const
	{
		return _Vec3(*this) /= rhs;
	}
	bool	operator==(const _Vec3& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y && rhs.z == z;
	}
	bool	operator!=(const _Vec3& rhs) const
	{
		return !(*this == rhs);
	}
	_Vec3& Saturate()
	{
		this->x = std::min(1.0f, std::max(0.0f, this->x));
		this->y = std::min(1.0f, std::max(0.0f, this->y));
		this->z = std::min(1.0f, std::max(0.0f, this->z));
		return *this;
	}
	_Vec3 GetSaturated() const	// clamp intensity of light to max 1 
	{
		_Vec3 temp(*this);
		temp.Saturate();
		return temp;
	}
	_Vec3& Hadamard(const _Vec3& rhs)	// multiple vector component by component 
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}
	_Vec3 GetHadamard(const _Vec3& rhs) const
	{
		_Vec3 temp(*this);
		temp.Hadamard(rhs);
		return temp;
	}
public:
	T z;
};

typedef _Vec3<float> Vec3;
typedef _Vec3<double> Ved3;
typedef _Vec3<int> Vei3;