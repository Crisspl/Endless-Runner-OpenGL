#include "Mat4.h"

#include <cstring>
#include "Maths_funcs.h"

namespace fhl
{

Mat4::Mat4()
{
	std::memset(m_elements, 0, 16 * sizeof(float));
}

Mat4::Mat4(float _diagonal)
	: Mat4()
{
	m_elements[0 + 0 * 4] = _diagonal;
	m_elements[1 + 1 * 4] = _diagonal;
	m_elements[2 + 2 * 4] = _diagonal;
	m_elements[3 + 3 * 4] = _diagonal;
}

Mat4::Mat4(Vec4f _r1, Vec4f _r2, Vec4f _r3, Vec4f _r4)
{
	m_rows[0] = _r1;
	m_rows[1] = _r2;
	m_rows[2] = _r3;
	m_rows[3] = _r4;
}

Mat4 operator*(const Mat4& _mat, float _n)
{
	Mat4 ret = _mat;
	for (size_t i = 0; i < 16; i++)
		ret.m_elements[i] *= _n;
	return ret;
}

Mat4 Mat4::operator*(const Mat4 & _other)
{
	Mat4 ret;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			ret.m_elements[i + j] = getRow(i).dot(_other.getCol(j));
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
	return m_rows[_n];
}

Vec4f Mat4::getCol(size_t _n) const
{
	return{ m_elements[_n], m_elements[_n + 4], m_elements[_n + 8], m_elements[_n + 12] };
}

Mat4 & Mat4::setRow(size_t _n, Vec4f _r)
{
	m_rows[_n] = _r;
	return *this;
}

Mat4 & Mat4::setCol(size_t _n, Vec4f _c)
{
	m_elements[_n] = _c.x;
	m_elements[_n + 4] = _c.y;
	m_elements[_n + 8] = _c.z;
	m_elements[_n + 12] = _c.w;

	return *this;
}

Mat4 Mat4::ortho(float _left, float _right, float _bottom, float _top, float _near, float _far)
{
	Mat4 ret;

	ret.m_elements[0 + 0 * 4] = 2.f / (_right - _left);
	ret.m_elements[3 + 0 * 4] = -(_right + _left) / (_right - _left);
	ret.m_elements[1 + 1 * 4] = 2.f / (_top - _bottom);
	ret.m_elements[3 + 1 * 4] = -(_top + _bottom) / (_top - _bottom);
	ret.m_elements[2 + 2 * 4] = -2.f / (_far - _near);
	ret.m_elements[3 + 3 * 4] = -(_far + _near) / (_far - _near);
	ret.m_elements[3 + 3 * 4] = 1.f;

	return ret;
}

Mat4 Mat4::perspective(float _fov, float _aspectRatio, float _near, float _far)
{
	Mat4 ret(1.f);

	float q = 1.f / ::tan(toRadians(0.5f * _fov));
	float a = q / _aspectRatio;

	float b = (_near + _far) / (_near - _far);
	float c = (2.0f * _near * _far) / (_near - _far);

	ret.m_elements[0 + 0 * 4] = a;
	ret.m_elements[1 + 1 * 4] = q;
	ret.m_elements[2 + 2 * 4] = b;
	ret.m_elements[2 + 3 * 4] = -1.0f;
	ret.m_elements[3 + 2 * 4] = c;

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

	return ret * translate(Vec3f(-_eye.x, -_eye.y, -_eye.z));
}

Mat4 Mat4::translate(const Vec3f& _t)
{
	Mat4 ret(1.f);

	ret.m_elements[3 + 0 * 4] = _t.x;
	ret.m_elements[3 + 1 * 4] = _t.y;
	ret.m_elements[3 + 2 * 4] = _t.z;

	return ret;
}

Mat4 Mat4::translate(Mat4 _mat, const Vec3f & _t)
{
	return _mat * translate(_t);
}

Mat4 Mat4::scale(const Vec3f & _s)
{
	Mat4 ret(1.f);

	ret.m_elements[0] = _s.x;
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
}

Mat4 Mat4::rotate(Mat4 _mat, float _angle, const Vec3f & _axe)
{
	return _mat * rotate(_angle, _axe);
}

Mat4 Mat4::transpose(Mat4 _mat)
{
	return Mat4(
			Vec4f(_mat.m_rows[0].x, _mat.m_rows[1].x, _mat.m_rows[2].x, _mat.m_rows[3].x),
			Vec4f(_mat.m_rows[0].y, _mat.m_rows[1].y, _mat.m_rows[2].y, _mat.m_rows[3].y),
			Vec4f(_mat.m_rows[0].z, _mat.m_rows[1].z, _mat.m_rows[2].z, _mat.m_rows[3].z),
			Vec4f(_mat.m_rows[0].w, _mat.m_rows[1].w, _mat.m_rows[2].w, _mat.m_rows[3].w)
	);
}

Mat4 Mat4::transposed()
{
	return transpose(*this);
}

}