#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "Vec2.h"

namespace fhl {

	template<typename _T>
	struct Vec3
	{
		explicit Vec3(_T _scalar = 0) : x(_scalar), y(_scalar), z(_scalar) { }
		Vec3(_T _x, _T _y, _T _z) : x(_x), y(_y), z(_z) { }
		Vec3(Vec2<_T> _v, _T _n) : x(_v.x), y(_v.y), z(_n) { }

		template<typename _U>
		explicit Vec3(const Vec3<_U>& _other)
			: x(_T(_other.x)),
			  y(_T(_other.y)),
			  z(_T(_other.z))
		{ }


		friend Vec3<_T> operator+(const Vec3<_T>& _left, const Vec3<_T>& _right) { return { _left.x + _right.x, _left.y + _right.y, _left.z + _right.z }; }

		friend Vec3<_T> operator-(const Vec3<_T>& _left, const Vec3<_T>& _right) { return { _left.x - _right.x, _left.y - _right.y, _left.z - _right.z }; }

		friend Vec3<_T> operator*(const Vec3<_T>& _left, const Vec3<_T>& _right) { return { _left.x * _right.x, _left.y * _right.y, _left.z * _right.z }; }
		friend Vec3<_T> operator*(const Vec3<_T>& _v, _T _scalar) { return{ _v.x * _scalar, _v.y * _scalar, _v.z * _scalar }; }

		friend Vec3<_T> operator/(const Vec3<_T>& _left, const Vec3<_T>& _right) { return { _left.x / _right.x, _left.y / _right.y, _left.z / _right.z }; }
		friend Vec3<_T> operator/(const Vec3<_T>& _v, _T _scalar) { return { _v.x / _scalar, _v.y / _scalar, _v.z / _scalar }; }

		void operator+=(const Vec3<_T>& _other) { *this = *this + _other; }

		void operator-=(const Vec3<_T>& _other) { *this = *this - _other; }

		void operator*=(const Vec3<_T>& _other) { *this = *this * _other; }
		void operator*=(_T _scalar) { *this = *this * _scalar; }

		void operator/=(const Vec3<_T>& _other) { *this = *this / _other; }
		void operator/=(_T _scalar) { *this = *this / _scalar; }

		Vec3<_T> operator-() const { return Vec3<_T>(-x, -y, -z); }

		bool operator==(const Vec3<_T>& _other) const { return _other.x == x && _other.y == y && _other.z == z; }
		bool operator!=(const Vec3<_T>& _other) const { return !(*this == _other); }

		bool operator<(const Vec3<_T>& _other) const { return x < _other.x && y < _other.y && z < _other.z; }
		bool operator<=(const Vec3<_T>& _other) const { return x <= _other.x && y <= _other.y && z <= _other.z; }
		bool operator>(const Vec3<_T>& _other) const { return x > _other.x && y > _other.y && z > _other.z; }
		bool operator>=(const Vec3<_T>& _other) const { return x >= _other.x && y >= _other.y && z >= _other.z; }

		float length() const { return sqrt(x*x + y*y + z*z); }
		Vec3<_T> normalized() const { return *this / length(); }
		const _T* data() const { return &x; }

		_T & operator[](size_t _n) { return elements[_n]; }
		_T operator[](size_t _n) const { return elements[_n]; }

		float dot(const Vec3<_T>& _right) { return x * _right.x + y * _right.y + z * _right.z; }
		Vec3<_T> cross(const Vec3<_T>& _right) 
		{
			return
			Vec3<_T>(
				y * _right.z - z * _right.y,
				z * _right.x - x * _right.z,
				x * _right.y - y * _right.x
			);
		}

		friend std::ostream& operator<<(std::ostream& _os, const Vec3<_T>& _v)
		{
			return _os << '{' << _v.x << ", " << _v.y << ", " << _v.z << '}';
		}

	public:
		union 
		{
			union
			{
				_T x, r, s;
			};
			union
			{
				_T y, g, t;
			};
			union
			{
				_T z, b, p;
			};
			_T elements[3];
		};
	};

	using Vec3f = Vec3<float>;
	using Vec3lf = Vec3<double>;
	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned>;

} //ns


#endif // VEC3_H
