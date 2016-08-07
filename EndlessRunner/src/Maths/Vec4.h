#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <cmath>

namespace fhl {

	template<typename _T>
	struct Vec4
	{
		Vec4() : Vec4(0) { }
		explicit Vec4(_T _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) { }
		Vec4(_T _x, _T _y, _T _z, _T _w) : x(_x), y(_y), z(_z), w(_w) { }

		template<typename _U>
		explicit Vec4(const Vec4<_U>& _other)
			: x(static_cast<_T>(_other.x)),
			  y(static_cast<_T>(_other.y)),
			  z(static_cast<_T>(_other.z)),
			  w(static_cast<_T>(_other.w))
		{ }


		friend Vec4<_T> operator+(const Vec4<_T>& _left, const Vec4<_T>& _right) { return{ _left.x + _right.x, _left.y + _right.y, _left.z + _right.z, _left.w + _right.w }; }

		friend Vec4<_T> operator-(const Vec4<_T>& _left, const Vec4<_T>& _right) { return{ _left.x - _right.x, _left.y - _right.y, _left.z - _right.z, _left.w - _right.w }; }

		friend Vec4<_T> operator*(const Vec4<_T>& _left, const Vec4<_T>& _right) { return{ _left.x * _right.x, _left.y * _right.y, _left.z * _right.z, _left.w * _right.w }; }
		friend Vec4<_T> operator*(const Vec4<_T>& _v, _T _scalar) { return{ _v.x * _scalar, _v.y * _scalar, _v.z * _scalar, _v.w / _scalar }; }

		friend Vec4<_T> operator/(const Vec4<_T>& _left, const Vec4<_T>& _right) { return{ _left.x / _right.x, _left.y / _right.y, _left.z / _right.z, _left.w / _right.w }; }
		friend Vec4<_T> operator/(const Vec4<_T>& _v, _T _scalar) { return{ _v.x / _scalar, _v.y / _scalar, _v.z / _scalar, _v.w / _scalar }; }

		void operator+=(const Vec4<_T>& _other) { *this = *this + _other; }

		void operator-=(const Vec4<_T>& _other) { *this = *this - _other; }

		void operator*=(const Vec4<_T>& _other) { *this = *this * _other; }
		void operator*=(_T _scalar) { *this = *this * _scalar; }

		void operator/=(const Vec4<_T>& _other) { *this = *this / _other; }
		void operator/=(_T _scalar) { *this = *this / _scalar; }

		Vec4 operator-() const { return{ -x, -y }; }

		bool operator==(const Vec4<_T>& _other) const { return _other.x == x && _other.y == y && _other.z == z; }
		bool operator!=(const Vec4<_T>& _other) const { return !(*this == _other); }

		bool operator<(const Vec4<_T>& _other) const { return x < _other.x && y < _other.y && z < _other.z && w < _other.w; }
		bool operator<=(const Vec4<_T>& _other) const { return x <= _other.x && y <= _other.y && z <= _other.z && w <= _other.w; }
		bool operator>(const Vec4<_T>& _other) const { return x > _other.x && y > _other.y && z > _other.z && w > _other.w; }
		bool operator>=(const Vec4<_T>& _other) const { return x >= _other.x && y >= _other.y && z >= _other.z && w >= _other.w; }

		const _T* data() const { return &x; }

		friend float dot(const Vec4<_T>& _left, const Vec4<_T>& _right) { return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z + _left.w * _right.w; }

		friend std::ostream& operator<<(std::ostream& _os, const Vec4<_T>& _v)
		{
			return _os << '{' << _v.x << ", " << _v.y << ", " << _v.z << ", " << _v.w << '}';
		}

	public:
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
		union
		{
			_T w, a, q;
		};
	};

	using Vec4f = Vec4<float>;
	using Vec4d = Vec4<double>;
	using Vec4i = Vec4<int>;
	using Vec4u = Vec4<unsigned>;

} //ns


#endif // VEC4_H
