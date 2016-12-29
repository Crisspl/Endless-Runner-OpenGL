#ifndef FHL_TRANSFORMABLE3D_H
#define FHL_TRANSFORMABLE3D_H

#include "Transform.h"
#include "Configurator.h"

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
		  virtual ~Transformable3D() { }

		  /* Setters */

		  Transformable3D& rotate(float _angle, Vec3f _axis = {0, 0, 1});

		  Transformable3D& setRotation(float _angle, Vec3f _axis = {0, 0, 1});

		  Transformable3D& move(Vec3f _offset);
		  /*
		  Transformable3D& setSize(Vec3f _size);
		  */
		  Transformable3D& setPosition(Vec3f _pos);

		  Transformable3D& setScale(Vec3f _scale);

		  Transformable3D& setOrigin(Vec2f _origin);

		  /* Getters */

		  RotationType getRotation() const { return m_rotation; }

		  Vec3f getSize() const { return m_size; }

		  Vec3f getScaledSize() const { return m_size * m_scale; }

		  Vec3f getPosition() const { return m_position; }

		  Vec3f getScale() const { return m_scale; }

		  Vec2f getOrigin() const { return m_transform.origin; }

		  Transform getTransform() const { return m_transform; }

	 protected:
		  RotationType m_rotation;
		  Vec3f m_size, m_position, m_scale;
		  Transform m_transform;
	 };

} // ns

#endif // FHL_TRANSFORMABLE3D_H
