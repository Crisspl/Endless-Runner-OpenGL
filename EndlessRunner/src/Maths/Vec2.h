#ifndef FHL_VEC2_H
#define FHL_VEC2_H

#include <iostream>
#include <cmath>

namespace fhl {

	 template<typename _T>
	 struct Vec2
	 {
		 explicit Vec2(_T _scalar = 0) : x(_scalar), y(_scalar) { }
		 Vec2(_T _x, _T _y) : x(_x), y(_y) { }

		 template<typename _U>
		 Vec2(const Vec2<_U>& _other) 
			 : x(_T(_other.x)),
				y(_T(_other.y))
		 { }


		 friend Vec2<_T> operator+(const Vec2<_T>& _left, const Vec2<_T>& _right) { return { _left.x + _right.x, _left.y + _right.y }; }

		 friend Vec2<_T> operator-(const Vec2<_T>& _left, const Vec2<_T>& _right) { return { _left.x - _right.x, _left.y - _right.y }; }

		 friend Vec2<_T> operator*(const Vec2<_T>& _left, const Vec2<_T>& _right) { return { _left.x * _right.x, _left.y * _right.y }; }
		 friend Vec2<_T> operator*(const Vec2<_T>& _v, _T _scalar) { return { _v.x * _scalar, _v.y * _scalar }; }

		 friend Vec2<_T> operator/(const Vec2<_T>& _left, const Vec2<_T>& _right) { return { _left.x / _right.x, _left.y / _right.y }; }
		 friend Vec2<_T> operator/(const Vec2<_T>& _v, _T _scalar) { return { _v.x / _scalar, _v.y / _scalar }; }

		 void operator+=(const Vec2<_T>& _other) { *this = *this + _other; }

		 void operator-=(const Vec2<_T>& _other) { *this = *this - _other; }

		 void operator*=(const Vec2<_T>& _other) { *this = *this * _other; }
		 void operator*=(_T _scalar) { *this = *this * _scalar; }

		 void operator/=(const Vec2<_T>& _other) { *this = *this / _other; }
		 void operator/=(_T _scalar) { *this = *this / _scalar; }

		 Vec2<_T> operator-() const { return Vec2<_T>(-x, -y); }

		 bool operator==(const Vec2<_T>& _other) const { return _other.x == x && _other.y == y; }
		 bool operator!=(const Vec2<_T>& _other) const { return !(*this == _other); }

		 bool operator<(const Vec2<_T>& _other) const { return x < _other.x && y < _other.y; }
		 bool operator<=(const Vec2<_T>& _other) const { return x <= _other.x && y <= _other.y; }
		 bool operator>(const Vec2<_T>& _other) const { return x > _other.x && y > _other.y; }
		 bool operator>=(const Vec2<_T>& _other) const { return x >= _other.x && y >= _other.y; }

		 float length() const { return sqrt(x*x + y*y); }
		 Vec2<_T> normalized() const { return *this / length(); }
		 const _T* data() const { return &x; }

		 _T & operator[](size_t _n) { return *(&x + _n); }
		 _T operator[](size_t _n) const { return *(&x + _n); }

		 float dot(const Vec2<_T>& _right) const { return x * _right.x + y * _right.y; }

		 friend std::ostream& operator<<(std::ostream& _os, const Vec2<_T>& _v)
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
