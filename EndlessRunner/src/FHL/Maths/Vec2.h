#ifndef FHL_VEC2_H
#define FHL_VEC2_H

#include <iostream>
#include <cmath>

namespace fhl {

	 template<typename _T>
	 struct Vec2
	 {
		  using valueType = _T;
		  enum { Dimensions = 2 };

		  explicit constexpr Vec2(_T _scalar = 0) : x(_scalar), y(_scalar) { }
		  constexpr Vec2(_T _x, _T _y) : x(_x), y(_y) { }

		  template<typename _U>
		  constexpr Vec2(const Vec2<_U> & _other) :
				x(_T(_other.x)),
				y(_T(_other.y))
		  { }

		  static constexpr Vec2<_T> up() { return{ 0, 1 }; }
		  static constexpr Vec2<_T> down() { return{ 0, -1 }; }
		  static constexpr Vec2<_T> right() { return{ 1, 0 }; }
		  static constexpr Vec2<_T> left() { return{ -1, 0 }; }
		  static constexpr Vec2<_T> zero() { return{ 0, 0 }; }
		  static constexpr Vec2<_T> one() { return{ 1, 1 }; }

		  friend constexpr Vec2<_T> operator+(const Vec2<_T> & _left, const Vec2<_T> & _right) { return { _left.x + _right.x, _left.y + _right.y }; }

		  friend constexpr Vec2<_T> operator-(const Vec2<_T> & _left, const Vec2<_T> & _right) { return { _left.x - _right.x, _left.y - _right.y }; }

		  friend constexpr Vec2<_T> operator*(const Vec2<_T> & _left, const Vec2<_T> & _right) { return { _left.x * _right.x, _left.y * _right.y }; }
		  friend constexpr Vec2<_T> operator*(const Vec2<_T> & _v, _T _scalar) { return { _v.x * _scalar, _v.y * _scalar }; }
		  friend constexpr Vec2<_T> operator*(_T _scalar, const Vec2<_T> & _v) { return _v * _scalar; }

		  friend constexpr Vec2<_T> operator/(const Vec2<_T> & _left, const Vec2<_T> & _right) { return { _left.x / _right.x, _left.y / _right.y }; }
		  friend constexpr Vec2<_T> operator/(const Vec2<_T> & _v, _T _scalar) { return { _v.x / _scalar, _v.y / _scalar }; }

		  Vec2<_T> & operator+=(const Vec2<_T> & _other) { return *this = *this + _other; }

		  Vec2<_T> & operator-=(const Vec2<_T> & _other) { return *this = *this - _other; }

		  Vec2<_T> & operator*=(const Vec2<_T> & _other) { return *this = *this * _other; }
		  Vec2<_T> & operator*=(_T _scalar) { return *this = *this * _scalar; }

		  Vec2<_T> & operator/=(const Vec2<_T> & _other) { return *this = *this / _other; }
		  Vec2<_T> & operator/=(_T _scalar) { return *this = *this / _scalar; }

		  constexpr Vec2<_T> operator-() const { return Vec2<_T>(-x, -y); }

		  constexpr bool operator==(const Vec2<_T> & _other) const { return _other.x == x && _other.y == y; }
		  constexpr bool operator!=(const Vec2<_T> & _other) const { return !(*this == _other); }

		  constexpr bool operator<(const Vec2<_T> & _other) const { return x < _other.x && y < _other.y; }
		  constexpr bool operator<=(const Vec2<_T> & _other) const { return x <= _other.x && y <= _other.y; }
		  constexpr bool operator>(const Vec2<_T> & _other) const { return x > _other.x && y > _other.y; }
		  constexpr bool operator>=(const Vec2<_T> & _other) const { return x >= _other.x && y >= _other.y; }

		  constexpr float length() const { return sqrt(x*x + y*y); }
		  constexpr Vec2<_T> normalized() const { return *this / length(); }
		  constexpr const _T * data() const { return &x; }

		  _T & operator[](std::size_t _n) { return *(&x + _n); }
		  constexpr _T operator[](std::size_t _n) const { return *(&x + _n); }

		  constexpr float dot(const Vec2<_T> & _right) const { return x * _right.x + y * _right.y; }

		  friend std::ostream & operator<<(std::ostream & _os, const Vec2<_T> & _v)
		  {
				return _os << '{' << _v.x << ", " << _v.y << '}';
		  }

	 public:
		  _T x, y;
	 };

	 using Vec2f = Vec2<float>;
	 using Vec2lf = Vec2<double>;
	 using Vec2i = Vec2<int>;
	 using Vec2u = Vec2<unsigned>;

} //ns


#endif // FHL_VEC2_H
