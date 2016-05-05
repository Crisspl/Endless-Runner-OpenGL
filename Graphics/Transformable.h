#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <utility>

#include "Transform.h"
#include "Configurator.h"

namespace gr
{

struct TransformData
{
   glm::vec2 position;
   glm::vec2 scale;
   glm::vec2 origin;
   float rotation;
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
   std::pair<Transform, bool> m_drawWithTransform;
};

} // ns
