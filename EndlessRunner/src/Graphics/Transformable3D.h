#ifndef FHL_TRANSFORMABLE3D_H
#define FHL_TRANSFORMABLE3D_H

#include "TransformMatrices.h"

namespace fhl
{

	 class Transformable3D
	 {
	 public:
		  struct RotationType
		  {
				float angle;
				Vec3f axis;
		  };

	 public:
		  Transformable3D();
		  virtual ~Transformable3D() = default;

		  Transformable3D & rotate(float _angle, const Vec3f & _axis);
		  Transformable3D & setRotation(float _angle, const Vec3f & _axis);
		  Transformable3D & move(const Vec3f & _offset);
		  Transformable3D & setPosition(const Vec3f & _pos);
		  Transformable3D & scale(const Vec3f & _scale);
		  Transformable3D & setScale(const Vec3f & _scale);
		  //Transformable3D& setOrigin(Vec3f _origin); /* TODO */
		  Transformable3D & setSize(const Vec3f & _size) { m_size = _size; return *this; }

		  RotationType getRotation() const { return m_rotation; }
		  Vec3f getSize() const { return m_size; }
		  Vec3f getScaledSize() const { return m_size * m_scale; }
		  Vec3f getPosition() const { return m_position; }
		  Vec3f getScale() const { return m_scale; }
		  //Vec2f getOrigin() const { return m_transform.origin; } /* TODO */

		  Mat4 getTransform() const;
		  Mat4 getMVP() const;
		  TransformMatrices getMatrices() const { return{ getTransform(), getMVP() }; }

	 private:
		  RotationType m_rotation;
		  Vec3f m_size, m_position, m_scale;
		  mutable Mat4 m_transform, m_mvp;
		  mutable bool m_transformChanged, m_mvpChanged;
	 };

} // ns

#endif // FHL_TRANSFORMABLE3D_H
