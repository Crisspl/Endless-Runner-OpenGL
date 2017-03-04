#ifndef FHL_VEC3_H
#define FHL_VEC3_H

#include <iostream>
#include <cmath>

#include "Vec2.h"

namespace fhl {

	template<typename _T>
	struct Vec3
	{
		  using valueType = _T;
		  enum { Dimensions = 3 };

		  explicit constexpr Vec3(_T _scalar = 0) : x(_scalar), y(_scalar), z(_scalar) { }
		  constexpr Vec3(_T _x, _T _y, _T _z) : x(_x), y(_y), z(_z) { }
		  constexpr Vec3(const Vec2<_T> & _v, _T _n) : x(_v.x), y(_v.y), z(_n) { }

		  template<typename _U>
		  constexpr Vec3(const Vec3<_U> & _other) :
				x(_T(_other.x)),
				y(_T(_other.y)),
				z(_T(_other.z))
		  { }

		  static constexpr Vec3<_T> up() { return{ 0, 1, 0 }; }
		  static constexpr Vec3<_T> down() { return{ 0, -1, 0 }; }
		  static constexpr Vec3<_T> right() { return{ 1, 0, 0 }; }
		  static constexpr Vec3<_T> left() { return{ -1, 0, 0 }; }
		  static constexpr Vec3<_T> forward() { return{ 0, 0, -1 }; }
		  static constexpr Vec3<_T> back() { return{ 0, 0, 1 }; }
		  static constexpr Vec3<_T> zero() { return{ 0, 0, 0 }; }
		  static constexpr Vec3<_T> one() { return{ 1, 1, 1 }; }

		  friend constexpr Vec3<_T> operator+(const Vec3<_T> & _left, const Vec3<_T> & _right) { return{ _left.x + _right.x, _left.y + _right.y, _left.z + _right.z }; }

		  friend constexpr Vec3<_T> operator-(const Vec3<_T> & _left, const Vec3<_T> & _right) { return{ _left.x - _right.x, _left.y - _right.y, _left.z - _right.z }; }

		  friend constexpr Vec3<_T> operator*(const Vec3<_T> & _left, const Vec3<_T> & _right) { return{ _left.x * _right.x, _left.y * _right.y, _left.z * _right.z }; }
		  friend constexpr Vec3<_T> operator*(const Vec3<_T> & _v, _T _scalar) { return{ _v.x * _scalar, _v.y * _scalar, _v.z * _scalar }; }
		  friend constexpr Vec3<_T> operator*(_T _scalar, const Vec3<_T> & _v) { return _v * _scalar; }

		  friend constexpr Vec3<_T> operator/(const Vec3<_T> & _left, const Vec3<_T> & _right) { return{ _left.x / _right.x, _left.y / _right.y, _left.z / _right.z }; }
		  friend constexpr Vec3<_T> operator/(const Vec3<_T> & _v, _T _scalar) { return{ _v.x / _scalar, _v.y / _scalar, _v.z / _scalar }; }

		  Vec3<_T> & operator+=(const Vec3<_T> & _other) { return *this = *this + _other; }

		  Vec3<_T> & operator-=(const Vec3<_T> & _other) { return *this = *this - _other; }

		  Vec3<_T> & operator*=(const Vec3<_T> & _other) { return *this = *this * _other; }
		  Vec3<_T> & operator*=(_T _scalar) { return *this = *this * _scalar; }

		  Vec3<_T> & operator/=(const Vec3<_T> & _other) { return *this = *this / _other; }
		  Vec3<_T> & operator/=(_T _scalar) { return *this = *this / _scalar; }

		  constexpr Vec3<_T> operator-() const { return Vec3<_T>(-x, -y, -z); }

		  constexpr bool operator==(const Vec3<_T> & _other) const { return _other.x == x && _other.y == y && _other.z == z; }
		  constexpr bool operator!=(const Vec3<_T> & _other) const { return !(*this == _other); }

		  constexpr bool operator<(const Vec3<_T> & _other) const { return x < _other.x && y < _other.y && z < _other.z; }
		  constexpr bool operator<=(const Vec3<_T> & _other) const { return x <= _other.x && y <= _other.y && z <= _other.z; }
		  constexpr bool operator>(const Vec3<_T> & _other) const { return x > _other.x && y > _other.y && z > _other.z; }
		  constexpr bool operator>=(const Vec3<_T> & _other) const { return x >= _other.x && y >= _other.y && z >= _other.z; }

		  constexpr float length() const { return sqrt(x*x + y*y + z*z); }
		  constexpr Vec3<_T> normalized() const { return *this / length(); }
		  constexpr const _T * data() const { return &x; }

		  _T & operator[](std::size_t _n) { return *(&x + _n); }
		  constexpr _T operator[](std::size_t _n) const { return *(&x + _n); }

		  constexpr float dot(const Vec3<_T> & _right) const { return x * _right.x + y * _right.y + z * _right.z; }
		  constexpr Vec3<_T> cross(const Vec3<_T> & _right) const
		  {
				return
				Vec3<_T>(
					 y * _right.z - z * _right.y,
					 z * _right.x - x * _right.z,
					 x * _right.y - y * _right.x
				);
		  }

		  friend std::ostream & operator<<(std::ostream & _os, const Vec3<_T> & _v)
		  {
				return _os << '{' << _v.x << ", " << _v.y << ", " << _v.z << '}';
		  }

	public:
		  _T x, y, z;
	};

	using Vec3f = Vec3<float>;
	using Vec3lf = Vec3<double>;
	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned>;

} //ns


#endif // FHL_VEC3_H
