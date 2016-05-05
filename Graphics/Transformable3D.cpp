#include "Transformable3D.h"

namespace gr
{

Transformable3D::Transformable3D()
   : m_rotation{ 0.f, glm::vec3(0.f) },
     m_position(0.f),
     m_scale(1.f)
{ }

Transformable3D& Transformable3D::rotate(float _angle, glm::vec3 _axis)
{
   while(_angle > 360.f)
      _angle -= 360.f;
   m_rotation.angle += _angle;
   /* TODO update rotation axis */
   m_transform.rotate(_angle, _axis);
   return *this;
}

Transformable3D& Transformable3D::setRotation(float _angle, glm::vec3 _axis)
{
   while(_angle > 360.f)
      _angle -= 360.f;
   m_rotation.angle = _angle;
   m_rotation.axis = _axis;
   m_transform.setRotation(_angle, _axis);
   return *this;
}

Transformable3D& Transformable3D::move(glm::vec3 _offset)
{
   m_position += _offset;
   m_transform.move(_offset);
   return *this;
}

/*
Transformable3D& Transformable3D::setSize(glm::vec2 _size)
{
   glm::vec2 oldOrigin = getOrigin();
   m_size = _size;
   setOrigin(oldOrigin);
   return *this;
}
*/

Transformable3D& Transformable3D::setPosition(glm::vec3 _pos)
{
   m_position = _pos;
   m_transform.setPosition(_pos);
   return *this;
}

Transformable3D& Transformable3D::setScale(glm::vec3 _scale)
{
   m_scale = _scale;
   m_transform.setScale(_scale);
   return *this;
}

Transformable3D& Transformable3D::setOrigin(glm::vec2 _origin)
{
   m_transform.origin = _origin;
   setRotation(m_rotation.angle, m_rotation.axis);
   setPosition(m_position);
   return *this;
}

} // ns
