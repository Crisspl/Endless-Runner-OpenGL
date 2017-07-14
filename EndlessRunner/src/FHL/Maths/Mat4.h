#ifndef FHL_MAT4_H
#define FHL_MAT4_H

#include <FHL/Maths/vectors.h>

namespace fhl
{

	struct Mat4
	{
		explicit Mat4(float _diagonal = 1.f);
		constexpr Mat4(const Vec4f & _c1, const Vec4f & _c2, const Vec4f & _c3, const Vec4f & _c4) : m_cols{ _c1, _c2, _c3, _c4 } {}

		Mat4 operator+(const Mat4 & _other) const;
		Mat4 & operator+=(const Mat4 & _other);

		Mat4 operator-(const Mat4 & _other) const;
		Mat4 & operator-=(const Mat4 & _other);

		Mat4 operator*(float _n) const;
		friend Mat4 operator*(float _n, const Mat4 & _m);
		Mat4 operator*(const Mat4 & _other) const;

		Mat4 & operator*=(float _n);
		Mat4 & operator*=(const Mat4 & _other);

		Mat4 operator-() const;

		bool operator==(const Mat4 & _other) const;
		bool operator!=(const Mat4 & _other) const;

		Vec4f getRow(size_t _n) const;
		Vec4f getCol(size_t _n) const;

		Mat4 & setRow(size_t _n, Vec4f _r);
		Mat4 & setCol(size_t _n, Vec4f _c);

		static Mat4 identity() { return Mat4(1.f); }

		static Mat4 ortho(float _left, float _right, float _bottom, float _top, float _near, float _far);
		static Mat4 perspective(float _fov, float _aspectRatio, float _near, float _far);
		static Mat4 lookAt(const Vec3f & _eye, const Vec3f & _center, const Vec3f & _up);

		static Mat4 translate(const Vec3f & _t);
		static Mat4 translate(const Mat4 & _mat, const Vec3f & _t);

		static Mat4 scale(const Vec3f& _s);
		static Mat4 scale(const Mat4 & _mat, const Vec3f & _s);

		static Mat4 rotate(float _angle, const Vec3f & _axe);
		static Mat4 rotate(const Mat4 & _mat, float _angle, const Vec3f & _axe);

		static Mat4 transpose(const Mat4 & _mat);
		Mat4 transposed() const;

		static Mat4 invert(const Mat4 & _mat);
		Mat4 inverted() const;

		template<typename _T>
		static Vec2<_T> transform(const Mat4 & _mat, const Vec2<_T> & _v);
		template<typename _T>
		static Vec3<_T> transform(const Mat4 & _mat, const Vec3<_T> & _v);

		float & operator[](std::size_t _n) { return m_cols[_n / 4][_n % 4]; }
		constexpr float operator[] (std::size_t _n) const { return m_cols[_n / 4][_n % 4]; }

		constexpr const float * data() const { return m_cols->data(); }

	private:
		Vec4f m_cols[4];
	};

	 template<typename _T>
	 Vec2<_T> Mat4::transform(const Mat4 & _mat, const Vec2<_T> & _v)
	 {
		  auto calc = [&_mat, &_v](std::size_t _n) -> _T {
			  return _mat.getRow(_n).dot(fhl::Vec4f(_v, fhl::Vec2f::one()));
		  };

		  return Vec2<_T>(calc(0), calc(1));
	 }

	 template<typename _T>
	 Vec3<_T> Mat4::transform(const Mat4 & _mat, const Vec3<_T> & _v)
	 {
		  auto calc = [&_mat, &_v](std::size_t _n) -> _T {
				return _mat.getRow(_n).dot(fhl::Vec4f(_v, 1));
		  };

		  return Vec3<_T>(calc(0), calc(1), calc(2));
	 }

}

#endif
