#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

namespace fhl {

	template<typename _T>
	struct Vec3
	{
		Vec3() : Vec3(0) { }
		explicit Vec3(_T _scalar) : x(_scalar), y(_scalar), z(_scalar) { }
		Vec3(_T _x, _T _y, _T _z) : x(_x), y(_y), z(_z) { }

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

		Vec3 operator-() const { return{ -x, -y }; }

		bool operator==(const Vec3<_T>& _other) const { return _other.x == x && _other.y == y && _other.z == z; }
		bool operator!=(const Vec3<_T>& _other) const { return !(*this == _other); }

		bool operator<(const Vec3<_T>& _other) const { return x < _other.x && y < _other.y && z < _other.z; }
		bool operator<=(const Vec3<_T>& _other) const { return x <= _other.x && y <= _other.y && z <= _other.z; }
		bool operator>(const Vec3<_T>& _other) const { return x > _other.x && y > _other.y && z > _other.z; }
		bool operator>=(const Vec3<_T>& _other) const { return x >= _other.x && y >= _other.y && z >= _other.z; }

		float length() const { return sqrt(x*x + y*y + z*z); }
		Vec3<_T> normalized() const { return *this / length(); }
		const _T* data() const { return &x; }

		friend float dot(const Vec3<_T>& _left, const Vec3<_T>& _right) { return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z; }
		friend Vec3<_T> cross(const Vec3<_T>& _left, const Vec3<_T>& _right) 
		{
			return
			{
				_left.y * _right.z - _left.z * _right.y,
				_left.z * _right.x - _left.x * _right.z,
				_left.x * _right.y - _left.y * _right.x
			};
		}

		friend std::ostream& operator<<(std::ostream& _os, const Vec3<_T>& _v)
		{
			return _os << '{' << _v.x << ", " << _v.y << ", " << _v.z << '}';
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
	};

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned>;

} //ns


#endif // VEC3_H
