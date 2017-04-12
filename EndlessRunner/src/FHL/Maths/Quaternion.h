#ifndef FHL_QUATERNION_H
#define FHL_QUATERNION_H

#include "vectors.h"
#include "Mat4.h"

namespace fhl
{

	 class Quaternion
	 {
	 public:
		  Quaternion();
		  Quaternion(float _x, float _y, float _z, float _angle);
		  Quaternion(Vec3f _axis, float _angle);

		  Quaternion operator*(Quaternion _other) const;
		  Quaternion & operator*=(const Quaternion & _other);

		  bool operator==(const Quaternion & _other) { return m_xyzw == _other.m_xyzw; }
		  bool operator!=(const Quaternion & _other) { return m_xyzw != _other.m_xyzw; }

		  Vec3f getAxis() const;
		  float getAngle() const;
		  Vec4f asVec4() const { return m_xyzw; }
		  Mat4 toMat4() const;

		  float length() const;
		  float dot(const Quaternion & _other) const;
		  Quaternion normalized() const;
		  Quaternion inverted() const;
		  Quaternion conjugate() const;

		  static Quaternion identity() { return Quaternion(); }

	 private:
		  Vec4f m_xyzw;
	 };

} // ns

#endif // FHL_QUATERNION_H
