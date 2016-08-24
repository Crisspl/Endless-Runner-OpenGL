#ifndef MAT4_H
#define MAT4_H

#include "Vec3.h"
#include "Vec4.h"

namespace fhl
{

struct Mat4
{
	Mat4();
	explicit Mat4(float _diagonal);
	Mat4(Vec4f _r1, Vec4f _r2, Vec4f _r3, Vec4f _r4);

	friend Mat4 operator*(const Mat4& _mat, float _n);
	Mat4 operator*(const Mat4 & _other);

	void operator*=(float _n);
	void operator*=(const Mat4 & _other);

	Vec4f getRow(size_t _n) const;
	Vec4f getCol(size_t _n) const;

	Mat4& setRow(size_t _n, Vec4f _r);
	Mat4& setCol(size_t _n, Vec4f _c);

	static Mat4 identity() { return Mat4(1.f); }

	static Mat4 ortho(float _left, float _right, float _bottom, float _top, float _near, float _far);
	static Mat4 perspective(float _fov, float _aspectRatio, float _near, float _far);
	static Mat4 lookAt(const Vec3f& _eye, const Vec3f& _center, const Vec3f& _up);
	static Mat4 translate(const Vec3f& _t);
	static Mat4 translate(Mat4 _mat, const Vec3f& _t);
	static Mat4 scale(const Vec3f& _s);
	static Mat4 scale(Mat4 _mat, const Vec3f& _s);
	static Mat4 rotate(float _angle, const Vec3f& _axe);
	static Mat4 rotate(Mat4 _mat, float _angle, const Vec3f& _axe);
	static Mat4 transpose(Mat4 _mat);
	Mat4 transposed();

	const float* data() const { return m_elements; }


private:
	union
	{
		Vec4f m_rows[4];
		float m_elements[16];
	};
};

}

#endif // MAT4_H
