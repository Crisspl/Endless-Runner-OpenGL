#include "Mat4.h"

#include <cstring>
#include "Maths_funcs.h"

namespace fhl
{

Mat4::Mat4(float _diagonal)
	: Mat4()
{
	std::memset(m_elements, 0, 16 * sizeof(*m_elements));

	m_elements[0 + 0 * 4] = _diagonal;
	m_elements[1 + 1 * 4] = _diagonal;
	m_elements[2 + 2 * 4] = _diagonal;
	m_elements[3 + 3 * 4] = _diagonal;
}

Mat4::Mat4(Vec4f _c1, Vec4f _c2, Vec4f _c3, Vec4f _c4)
{
	m_cols[0] = _c1;
	m_cols[1] = _c2;
	m_cols[2] = _c3;
	m_cols[3] = _c4;
}

Mat4 operator*(const Mat4& _mat, float _n)
{
	Mat4 ret = _mat;
	for (int i = 0; i < 16; i++)
		ret.m_elements[i] *= _n;
	return ret;
}

Mat4 Mat4::operator*(const Mat4 & _other)
{
	Mat4 ret;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			float sum = 0;
			for (int e = 0; e < 4; e++)
				sum += m_elements[i + e * 4] * _other.m_elements[e + j * 4];
			ret.m_elements[i + j * 4] = sum;
		}
	}
	return ret;
}

void Mat4::operator*=(float _n)
{
	*this = *this * _n;
}

void Mat4::operator*=(const Mat4 & _other)
{
	*this = *this * _other;
}

Vec4f Mat4::getRow(size_t _n) const
{
	Vec4f row;
	for (int i = 0; i < 4; i++)
		row[i] = m_elements[_n + i * 4];

	return row;
}

Vec4f Mat4::getCol(size_t _n) const
{
	return m_cols[_n];
}

Mat4 & Mat4::setRow(size_t _n, Vec4f _r)
{
	for (int i = 0; i < 4; i++)
		m_elements[_n + i * 4] = _r[i];

	return *this;
}

Mat4 & Mat4::setCol(size_t _n, Vec4f _c)
{
	m_cols[_n] = _c;
	return *this;
}

Mat4 Mat4::ortho(float _left, float _right, float _bottom, float _top, float _near, float _far)
{
	Mat4 ret;

	ret.m_elements[0 + 0 * 4] = 2.f / (_right - _left);
	ret.m_elements[1 + 1 * 4] = 2.f / (_top - _bottom);
	ret.m_elements[2 + 2 * 4] = -2.f / (_far - _near);
	ret.setCol(3,
		{ -((_right + _left) / (_right - _left)),
			(_top + _bottom) / (_top - _bottom),
			-((_far + _near) / (_far - _near)),
			1.f }
	);

	return ret;
}

Mat4 Mat4::perspective(float _fov, float _aspectRatio, float _near, float _far)
{
	Mat4 ret(0.f);

	float t = std::tan(toRadians(_fov / 2.f));

	ret.m_elements[0 + 0 * 4] = 1.f / (_aspectRatio * t);
	ret.m_elements[1 + 1 * 4] = 1.f / t;
	ret.m_elements[2 + 2 * 4] = -(_far + _near) / (_far - _near);
	ret.m_elements[3 + 2 * 4] = -1.0f;
	ret.m_elements[2 + 3 * 4] = -2.f * _far * _near / (_far - _near);

	return ret;
}

Mat4 Mat4::lookAt(const Vec3f & _eye, const Vec3f& _center, const Vec3f& _up)
{
	Mat4 ret(1.f);

	Vec3f f = (_center - _eye).normalized();
	Vec3f s = f.cross(_up.normalized());
	Vec3f u = s.cross(f);

	ret.m_elements[0 + 0 * 4] = s.x;
	ret.m_elements[0 + 1 * 4] = s.y;
	ret.m_elements[0 + 2 * 4] = s.z;

	ret.m_elements[1 + 0 * 4] = u.x;
	ret.m_elements[1 + 1 * 4] = u.y;
	ret.m_elements[1 + 2 * 4] = u.z;

	ret.m_elements[2 + 0 * 4] = -f.x;
	ret.m_elements[2 + 1 * 4] = -f.y;
	ret.m_elements[2 + 2 * 4] = -f.z;
	/* TODO */

	return ret * translate(-_eye);
}

Mat4 Mat4::translate(const Vec3f& _t)
{
	Mat4 ret(1.f);
	ret.setCol(3, Vec4f(_t, 1.f));

	return ret;
}

Mat4 Mat4::translate(Mat4 _mat, const Vec3f & _t)
{
	return _mat * translate(_t);
}

Mat4 Mat4::scale(const Vec3f & _s)
{
	Mat4 ret(1.f);

	ret.m_elements[0 + 4 * 0] = _s.x;
	ret.m_elements[1 + 4 * 1] = _s.y;
	ret.m_elements[2 + 4 * 2] = _s.z;

	return ret;
}

Mat4 Mat4::scale(Mat4 _mat, const Vec3f & _s)
{
	return _mat * scale(_s);
}

Mat4 Mat4::rotate(float _angle, const Vec3f & _axe)
{
	Mat4 ret(1.f);

	float x = _axe.x;
	float y = _axe.y;
	float z = _axe.z;

	float angle = toRadians(_angle);
	float s = ::sin(angle);
	float c = ::cos(angle);
	float omc = 1.f - c;

	ret.m_elements[0 + 0 * 4] = x * x * omc + c;
	ret.m_elements[0 + 1 * 4] = x * y * omc + z * s;
	ret.m_elements[0 + 2 * 4] = x * z * omc - y * s;
	
	ret.m_elements[1 + 0 * 4] = x * y * omc - z * s;
	ret.m_elements[1 + 1 * 4] = y * y * omc + c;
	ret.m_elements[1 + 2 * 4] = y * z * omc + x * s;

	ret.m_elements[2 + 0 * 4] = x * z * omc + y * s;
	ret.m_elements[2 + 1 * 4] = y * z * omc - x * s;
	ret.m_elements[2 + 2 * 4] = z * z * omc + c;

	return ret;
	/* TODO */
}

Mat4 Mat4::rotate(Mat4 _mat, float _angle, const Vec3f & _axe)
{
	return _mat * rotate(_angle, _axe);
	/* TODO */
}

Mat4 Mat4::transpose(const Mat4 & _mat)
{
	Mat4 trans;
	for (int i = 0; i < 4; i++)
		trans.setCol(i, _mat.getRow(i));

	return trans;
}

Mat4 Mat4::transposed() const
{
	return transpose(*this);
}

Mat4 Mat4::invert(const Mat4 & _mat)
{
	Mat4 inv;
	float * e = inv.m_elements;
	const float * m = _mat.m_elements;

	e[0] = m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[13] * m[6] * m[11] - (m[13] * m[10] * m[7] + m[9] * m[6] * m[15] + m[5] * m[14] * m[11]);
	e[4] = (m[1] * m[10] * m[15] + m[9] * m[14] * m[3] + m[13] * m[2] * m[11] - (m[13] * m[10] * m[3] + m[9] * m[2] * m[15] + m[1] * m[14] * m[11])) * -1.f;
	e[8] = m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[13] * m[2] * m[7] - (m[13] * m[6] * m[3] + m[5] * m[2] * m[15] + m[1] * m[14] * m[7]);
	e[12] = (m[1] * m[6] * m[11] + m[5] * m[10] * m[3] + m[9] * m[2] * m[7] - (m[9] * m[6] * m[3] + m[5] * m[2] * m[11] + m[1] * m[10] * m[7])) * -1.f;
	e[1] = (m[4] * m[10] * m[15] + m[8] * m[14] * m[7] + m[12] * m[6] * m[11] - (m[12] * m[10] * m[7] + m[8] * m[6] * m[15] + m[4] * m[14] * m[11])) * -1.f;
	e[5] = m[0] * m[10] * m[15] + m[8] * m[14] * m[3] + m[12] * m[2] * m[11] - (m[12] * m[10] * m[3] + m[8] * m[2] * m[15] + m[0] * m[14] * m[11]);
	e[9] = (m[0] * m[6] * m[15] + m[4] * m[14] * m[3] + m[12] * m[2] * m[7] - (m[12] * m[6] * m[3] + m[4] * m[2] * m[15] + m[0] * m[14] * m[7])) * -1.f;
	e[13] = m[0] * m[6] * m[11] + m[4] * m[10] * m[3] + m[8] * m[2] * m[7] - (m[8] * m[6] * m[3] + m[4] * m[2] * m[11] + m[0] * m[10] * m[7]);
	e[2] = m[4] * m[9] * m[15] + m[8] * m[13] * m[7] + m[12] * m[5] * m[11] - (m[12] * m[9] * m[7] + m[8] * m[5] * m[15] + m[4] * m[13] * m[11]);
	e[6] = (m[0] * m[9] * m[15] + m[8] * m[13] * m[3] + m[12] * m[1] * m[11] - (m[12] * m[9] * m[3] + m[8] * m[1] * m[15] + m[0] * m[13] * m[3])) * 1.f;
	e[10] = m[0] * m[5] * m[15] + m[4] * m[13] * m[3] + m[12] * m[1] * m[7] - (m[12] * m[5] * m[3] + m[4] * m[1] * m[15] + m[0] * m[13] * m[7]);
	e[14] = (m[0] * m[5] * m[11] + m[4] * m[9] * m[3] + m[8] * m[1] * m[7] - (m[8] * m[5] * m[3] + m[4] * m[1] * m[11] + m[0] * m[9] * m[7])) * -1.f;
	e[3] = (m[4] * m[9] * m[14] + m[8] * m[13] * m[6] + m[12] * m[5] * m[10] - (m[12] * m[9] * m[6] + m[8] * m[5] * m[14] + m[4] * m[13] * m[10])) * -1.f;
	e[7] = m[0] * m[9] * m[14] + m[8] * m[13] * m[2] + m[12] * m[1] * m[10] - (m[12] * m[9] * m[2] + m[8] * m[1] * m[14] + m[0] * m[13] * m[10]);
	e[11] = (m[0] * m[5] * m[14] + m[4] * m[13] * m[2] + m[12] * m[1] * m[6] - (m[12] * m[5] * m[2] + m[4] * m[1] * m[14] + m[0] * m[13] * m[6])) * -1.f;
	e[15] = m[0] * m[5] * m[10] + m[4] * m[9] * m[2] + m[12] * m[1] * m[6] - (m[8] * m[5] * m[2] + m[4] * m[1] * m[10] + m[0] * m[9] * m[6]);

	float det = m[0] * e[0] + m[4] * e[1] + m[8] * e[2] + m[12] * e[3];
	det = 1.f / det;

	inv = inv.transposed();
	inv *= det;

	return inv;
}

Mat4 fhl::Mat4::inverted() const
{
	return invert(*this);
}
