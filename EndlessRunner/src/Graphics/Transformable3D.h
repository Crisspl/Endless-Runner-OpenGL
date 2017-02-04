#ifndef FHL_TRANSFORMABLE3D_H
#define FHL_TRANSFORMABLE3D_H

#include "TransformMatrices.h"
#include "../Maths/Quaternion.h"

namespace fhl
{

	 class Transformable3D
	 {
	 public:
		  Transformable3D();
		  virtual ~Transformable3D() = default;

		  Transformable3D & rotate(float _angle, const Vec3f & _axis);
		  Transformable3D & setRotation(float _angle, const Vec3f & _axis);
		  Transformable3D & move(const Vec3f & _offset);
		  Transformable3D & setPosition(const Vec3f & _pos);
		  Transformable3D & scale(const Vec3f & _scale);
		  Transformable3D & setScale(const Vec3f & _scale);
		  Transformable3D & setOrigin(Vec3f _origin);

		  Quaternion getRotation() const { return m_rotation; }
		  Vec3f getPosition() const { return m_position; }
		  Vec3f getScale() const { return m_scale; }
		  Vec3f getOrigin() const { return m_origin; }

		  Mat4 getTransform() const;
		  Mat4 getMVP() const;
		  TransformMatrices getMatrices() const { return{ getTransform(), getMVP() }; }

		  static TransformMatrices createTransformMatrices(const Vec3f & _pos, const Vec3f & _scale, const Vec3f & _origin, const Quaternion & _rotation);
		  TransformMatrices calcModifiedTransformMatrices(const Vec3f & _mvOffset, const Vec3f & _scaleMlt, const Quaternion & _rotation) const;

	 private:
		  static Mat4 createTransformMatrix(const Vec3f & _pos, const Vec3f & _scale, const Vec3f & _origin, const Quaternion & _rotation);

	 private:
		  Quaternion m_rotation;
		  Vec3f m_position, m_scale, m_origin;
		  mutable Mat4 m_transform, m_mvp;
		  mutable bool m_transformChanged, m_mvpChanged;
	 };

} // ns

#endif // FHL_TRANSFORMABLE3D_H
