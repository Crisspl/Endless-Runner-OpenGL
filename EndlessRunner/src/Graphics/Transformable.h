#ifndef FHL_TRANSFORMABLE_H
#define FHL_TRANSFORMABLE_H

#include <GL/glew.h>

#include <utility>

#include "Transform.h"
#include "Configurator.h"

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
   virtual ~Transformable() { }

   /* Setters */

   Transformable& rotate(float _angle);

   Transformable& setRotation(float _angle);

   Transformable& move(Vec2f _offset);

   Transformable& setPosition(Vec2f _pos);

   Transformable& setScale(Vec2f _scale);

   Transformable& setOrigin(Vec2f _origin);

   /* Getters */

   float getRotation() const { return m_rotation; }

   Vec2f getPosition() const { return m_position; }

   Vec2f getScale() const { return m_scale; }

   Vec2f getOrigin() const { return m_transform.origin; }

   Transform getTransform() const { return m_transform; }

   TransformData getTransformData() const;

protected:
   float m_rotation;
   Vec2f m_position, m_scale;
   Transform m_transform;
};

} // ns

#endif // FHL_TRANSFORMABLE_H
