#ifndef TRANSFORMABLE3D_H
#define TRANSFORMABLE3D_H

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
      glm::vec3 axis;
   };

public:
   Transformable3D();
   virtual ~Transformable3D() { }

   /* Setters */

   Transformable3D& rotate(float _angle, glm::vec3 _axis = {0, 0, 1});

   Transformable3D& setRotation(float _angle, glm::vec3 _axis = {0, 0, 1});

   Transformable3D& move(glm::vec3 _offset);
/*
   Transformable3D& setSize(glm::vec3 _size);
*/
   Transformable3D& setPosition(glm::vec3 _pos);

   Transformable3D& setScale(glm::vec3 _scale);

   Transformable3D& setOrigin(glm::vec2 _origin);

   /* Getters */

   RotationType getRotation() const { return m_rotation; }

   glm::vec3 getSize() const { return m_size; }

   glm::vec3 getScaledSize() const { return m_size * m_scale; }

   glm::vec3 getPosition() const { return m_position; }

   glm::vec3 getScale() const { return m_scale; }

   glm::vec2 getOrigin() const { return m_transform.origin; }

protected:
   RotationType m_rotation;
   glm::vec3 m_size, m_position, m_scale;
   Transform m_transform;
};

} // ns

#endif // TRANSFORMABLE3D_H
