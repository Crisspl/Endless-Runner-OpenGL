#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <utility>

#include "Transform.h"
#include "Configurator.h"

namespace fhl
{

struct TransformData
{
   glm::vec2 botLeft;
   glm::vec2 scale;
   glm::vec2 origin;
   float rotation;

   glm::vec2 position() { return botLeft + origin; }
};

class Transformable
{
public:
   Transformable();
   virtual ~Transformable() { }

   /* Setters */

   Transformable& rotate(float _angle);

   Transformable& setRotation(float _angle);

   Transformable& move(glm::vec2 _offset);

   Transformable& setPosition(glm::vec2 _pos);

   Transformable& setScale(glm::vec2 _scale);

   Transformable& setOrigin(glm::vec2 _origin);

   /* Getters */

   float getRotation() const { return m_rotation; }

   glm::vec2 getPosition() const { return m_position; }

   glm::vec2 getScale() const { return m_scale; }

   glm::vec2 getOrigin() const { return m_transform.origin; }

   Transform getTransform() const { return m_transform; }

   TransformData getTransformData() const;

protected:
   float m_rotation;
   glm::vec2 m_position, m_scale;
   Transform m_transform;
};

} // ns

#endif // TRANSFORMABLE_H
