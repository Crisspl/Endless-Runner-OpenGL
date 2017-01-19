#ifndef FHL_TRANSFORMABLE_H
#define FHL_TRANSFORMABLE_H

#include <GL/glew.h>
#include <utility>

#include "TransformMatrices.h"

namespace fhl
{

	 struct TransformData
	 {
		  Vec2f botLeft;
		  Vec2f scale;
		  Vec2f origin;
		  float rotation;

		  Vec2f position() { return botLeft + origin; }
	 };

	 class Transformable
	 {
	 public:
		  Transformable();
		  virtual ~Transformable() = default;

		  Transformable & rotate(float _angle);
		  Transformable & setRotation(float _angle);
		  Transformable & move(const Vec2f & _offset);
		  Transformable & setPosition(const Vec2f & _pos);
		  Transformable & scale(const Vec2f & _scale);
		  Transformable & setScale(const Vec2f & _scale);
		  Transformable & setOrigin(const Vec2f & _origin);

		  float getRotation() const { return m_rotation; }
		  Vec2f getPosition() const { return m_position; }
		  Vec2f getScale() const { return m_scale; }
		  Vec2f getOrigin() const { return m_origin; }
		  TransformData getTransformData() const;

		  Mat4 getTransform() const;
		  Mat4 getMVP() const;
		  TransformMatrices getMatrices() const { return{ getTransform(), getMVP() }; }

	 private:
		  float m_rotation;
		  Vec2f m_position, m_scale, m_origin;
		  mutable Mat4 m_transform, m_mvp;
		  mutable bool m_transformChanged, m_mvpChanged;
	 };

} // ns

#endif // FHL_TRANSFORMABLE_H
