#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Transform.h"
#include "Configurator.h"

namespace gr
{

class Transformable
{
public:
   explicit Transformable(glm::vec2 _size = {1.f, 1.f});
   virtual ~Transformable() { }

   /* Setters */

   Transformable& rotate(float _angle);

   Transformable& setRotation(float _angle);

   Transformable& move(glm::vec2 _offset);

   Transformable& setSize(glm::vec2 _size);

   Transformable& setPosition(glm::vec2 _pos);

   Transformable& setScale(glm::vec2 _scale);

   Transformable& setOrigin(glm::vec2 _origin);

   /* Getters */

   float getRotation() const { return m_rotation; }

   glm::vec2 getSize() const
   {
      glm::vec2 size = m_size
      #ifdef PERSPECTIVE
         * Configurator::viewPortSize()
      #endif
      ;
      #ifdef PERSPECTIVE
         size.x *= Configurator::vpRatioYX();
      #endif
      return size;
   }

   glm::vec2 getPosition() const { return m_position; }

   glm::vec2 getScale() const { return m_scale; }

   glm::vec2 getOrigin() const { return m_transform.origin / m_size; }

protected:
   void updatePosArray();
   void uploadPosArray();

protected:
   float m_rotation;
   glm::vec2 m_position, m_scale, m_size;
   Transform m_transform;

   GLuint m_posBuffer;
   glm::vec2 m_posArray[4];
};

} // ns
