#include <FHL/Maths/Mat4.h>

#include <cstring>

#include <FHL/Maths/mathsFuncs.h>

namespace fhl
{

	 Mat4::Mat4(float _diagonal)
	 {
		 std::memset(m_cols, 0, 4 * sizeof(*m_cols));

		 for (int i = 0; i < 4; i++)
			 m_cols[i][i] = _diagonal;
	 }

	 Mat4 Mat4::operator+(const Mat4 & _other) const
	 {
		 Mat4 ret(*this);

		 for (int i = 0; i < 16; i++)
			 ret[i] += _other[i];

		 return ret;
	 }

	 Mat4 & Mat4::operator+=(const Mat4 & _other)
	 {
		 for (int i = 0; i < 16; i++)
			 (*this)[i] += _other[i];

		 return *this;
	 }

	 Mat4 Mat4::operator-(const Mat4 & _other) const
	 {
		 Mat4 ret(*this);

		 for (int i = 0; i < 16; i++)
			 ret[i] -= _other[i];

		 return ret;
	 }

	 Mat4 & Mat4::operator-=(const Mat4 & _other)
	 {
		 for (int i = 0; i < 16; i++)
			 (*this)[i] -= _other[i];

		 return *this;
	 }

	 Mat4 Mat4::operator*(float _n) const
	 {
		 Mat4 ret(*this);

		 for (int i = 0; i < 16; i++)
			 ret[i] *= _n;

		 return ret;
	 }

	 Mat4 operator*(float _n, const Mat4 & _m)
	 {
		 return _m * _n;
	 }

	 Mat4 Mat4::operator*(const Mat4 & _other) const
	 {
		 Mat4 ret;
		 for (int j = 0; j < 4; j++)
		 {
			 for (int i = 0; i < 4; i++)
			 {
				 float sum = 0;
				 for (int e = 0; e < 4; e++)
					 sum += (*this)[i + e * 4] * _other[e + j * 4];
				 ret[i + j * 4] = sum;
			 }
		 }
		 return ret;
	 }

	 Mat4 & Mat4::operator*=(float _n)
	 {
		 return (*this = *this * _n);
	 }

	 Mat4 & Mat4::operator*=(const Mat4 & _other)
	 {
		 return (*this = *this * _other);
	 }

	 Mat4 Mat4::operator-() const
	 {
		 return *this * -1.f;
	 }

	 bool Mat4::operator==(const Mat4 & _other) const
	 {
		 for (int i = 0; i < 4; i++)
			 if (m_cols[i] != _other.m_cols[i])
				 return false;
		 return true;
	 }

	 bool Mat4::operator!=(const Mat4 & _other) const
	 {
		 return !(*this == _other);
	 }

	 Vec4f Mat4::getRow(size_t _n) const
	 {
		 Vec4f row;
		 for (int i = 0; i < 4; i++)
			 row[i] = (*this)[_n + i * 4];

		 return row;
	 }

	 Vec4f Mat4::getCol(size_t _n) const
	 {
		 return m_cols[_n];
	 }

	 Mat4 & Mat4::setRow(size_t _n, Vec4f _r)
	 {
		 for (int i = 0; i < 4; i++)
			 (*this)[_n + i * 4] = _r[i];

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

		 ret[0 + 0 * 4] = 2.f / (_right - _left);
		 ret[1 + 1 * 4] = 2.f / (_top - _bottom);
		 ret[2 + 2 * 4] = -2.f / (_far - _near);
		 ret.setCol(3, {
			-((_right + _left) / (_right - _left)),
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

		 ret[0 + 0 * 4] = 1.f / (_aspectRatio * t);
		 ret[1 + 1 * 4] = 1.f / t;
		 ret[2 + 2 * 4] = -(_far + _near) / (_far - _near);
		 ret[3 + 2 * 4] = -1.0f;
		 ret[2 + 3 * 4] = -2.f * _far * _near / (_far - _near);

		 return ret;
	 }

	 Mat4 Mat4::lookAt(const Vec3f & _eye, const Vec3f & _center, const Vec3f & _up)
	 {
		 Mat4 ret(1.f);

		 const Vec3f f = (_center - _eye).normalized();
		 const Vec3f s = f.cross(_up).normalized();
		 const Vec3f u = s.cross(f);
		 const Vec3f t = Vec3f(-(s.dot(_eye)), -(u.dot(_eye)), f.dot(_eye));

		 ret.setRow(0, Vec4f(s, 0));
		 ret.setRow(1, Vec4f(u, 0));
		 ret.setRow(2, Vec4f(-f, 0));
		 ret.setCol(3, Vec4f(t, 1));

		 return ret;
	 }

	 Mat4 Mat4::translate(const Vec3f & _t)
	 {
		 Mat4 ret(1.f);
		 ret.setCol(3, Vec4f(_t, 1.f));

		 return ret;
	 }

	 Mat4 Mat4::translate(const Mat4 & _mat, const Vec3f & _t)
	 {
		 return _mat * translate(_t);
	 }

	 Mat4 Mat4::scale(const Vec3f & _s)
	 {
		 Mat4 ret(1.f);

		 ret[0 + 4 * 0] = _s.x();
		 ret[1 + 4 * 1] = _s.y();
		 ret[2 + 4 * 2] = _s.z();

		 return ret;
	 }

	 Mat4 Mat4::scale(const Mat4 & _mat, const Vec3f & _s)
	 {
		 return _mat * scale(_s);
	 }

	 Mat4 Mat4::rotate(float _angle, const Vec3f & _axe)
	 {
		 Mat4 ret(1.f);

		 float x = _axe.x();
		 float y = _axe.y();
		 float z = _axe.z();

		 float angle = toRadians(_angle);
		 float s = std::sin(angle);
		 float c = std::cos(angle);
		 float omc = 1.f - c;


		 ret.setRow(0,
		 {
			 x * x * omc + c,
			 x * y * omc - z * s,
			 x * z * omc + y * s,
			 0
		 });
		 ret.setRow(1,
		 {
			 x * y * omc + z * s,
			 y * y * omc + c,
			 y * z * omc - x * s,
			 0
		 });
		 ret.setRow(2,
		 {
			 x * z * omc - y * s,
			 y * z * omc - y * s,
			 z * z * omc + c,
			 0
		 });

		 return ret;
	 }

	 Mat4 Mat4::rotate(const Mat4 & _mat, float _angle, const Vec3f & _axe)
	 {
		 return _mat * rotate(_angle, _axe);
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
		 float * const e = &inv[0];
		 const float * const m = _mat.data();

		 e[0] = m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[13] * m[6] * m[11] - (m[13] * m[10] * m[7] + m[9] * m[6] * m[15] + m[5] * m[14] * m[11]);
		 e[4] = (m[1] * m[10] * m[15] + m[9] * m[14] * m[3] + m[13] * m[2] * m[11] - (m[13] * m[10] * m[3] + m[9] * m[2] * m[15] + m[1] * m[14] * m[11])) * -1.f;
		 e[8] = m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[13] * m[2] * m[7] - (m[13] * m[6] * m[3] + m[5] * m[2] * m[15] + m[1] * m[14] * m[7]);
		 e[12] = (m[1] * m[6] * m[11] + m[5] * m[10] * m[3] + m[9] * m[2] * m[7] - (m[9] * m[6] * m[3] + m[5] * m[2] * m[11] + m[1] * m[10] * m[7])) * -1.f;
		 e[1] = (m[4] * m[10] * m[15] + m[8] * m[14] * m[7] + m[12] * m[6] * m[11] - (m[12] * m[10] * m[7] + m[8] * m[6] * m[15] + m[4] * m[14] * m[11])) * -1.f;
		 e[5] = m[0] * m[10] * m[15] + m[8] * m[14] * m[3] + m[12] * m[2] * m[11] - (m[12] * m[10] * m[3] + m[8] * m[2] * m[15] + m[0] * m[14] * m[11]);
		 e[9] = (m[0] * m[6] * m[15] + m[4] * m[14] * m[3] + m[12] * m[2] * m[7] - (m[12] * m[6] * m[3] + m[4] * m[2] * m[15] + m[0] * m[14] * m[7])) * -1.f;
		 e[13] = m[0] * m[6] * m[11] + m[4] * m[10] * m[3] + m[8] * m[2] * m[7] - (m[8] * m[6] * m[3] + m[4] * m[2] * m[11] + m[0] * m[10] * m[7]);
		 e[2] = m[4] * m[9] * m[15] + m[8] * m[13] * m[7] + m[12] * m[5] * m[11] - (m[12] * m[9] * m[7] + m[8] * m[5] * m[15] + m[4] * m[13] * m[11]);
		 e[6] = (m[0] * m[9] * m[15] + m[8] * m[13] * m[3] + m[12] * m[1] * m[11] - (m[12] * m[9] * m[3] + m[8] * m[1] * m[15] + m[0] * m[13] * m[3])) * -1.f;
		 e[10] = m[0] * m[5] * m[15] + m[4] * m[13] * m[3] + m[12] * m[1] * m[7] - (m[12] * m[5] * m[3] + m[4] * m[1] * m[15] + m[0] * m[13] * m[7]);
		 e[14] = (m[0] * m[5] * m[11] + m[4] * m[9] * m[3] + m[8] * m[1] * m[7] - (m[8] * m[5] * m[3] + m[4] * m[1] * m[11] + m[0] * m[9] * m[7])) * -1.f;
		 e[3] = (m[4] * m[9] * m[14] + m[8] * m[13] * m[6] + m[12] * m[5] * m[10] - (m[12] * m[9] * m[6] + m[8] * m[5] * m[14] + m[4] * m[13] * m[10])) * -1.f;
		 e[7] = m[0] * m[9] * m[14] + m[8] * m[13] * m[2] + m[12] * m[1] * m[10] - (m[12] * m[9] * m[2] + m[8] * m[1] * m[14] + m[0] * m[13] * m[10]);
		 e[11] = (m[0] * m[5] * m[14] + m[4] * m[13] * m[2] + m[12] * m[1] * m[6] - (m[12] * m[5] * m[2] + m[4] * m[1] * m[14] + m[0] * m[13] * m[6])) * -1.f;
		 e[15] = m[0] * m[5] * m[10] + m[4] * m[9] * m[2] + m[8] * m[1] * m[6] - (m[8] * m[5] * m[2] + m[4] * m[1] * m[10] + m[0] * m[9] * m[6]);

		 float det = m[0] * e[0] + m[1] * e[1] + m[2] * e[2] + m[3] * e[3];
		 det = 1.f / det;

		 inv = inv.transposed();
		 inv *= det;

		 return inv;
	 }

	 Mat4 Mat4::inverted() const
	 {
		 return invert(*this);
	 }

}