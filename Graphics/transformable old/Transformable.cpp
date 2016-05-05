#include "Transformable.h"

namespace gr
{

Transformable::Transformable(glm::vec2 _size)
   : m_rotation(0.f),
     m_position(0.f, 0.f),
     m_scale(1.f, 1.f),
//#ifdef PERSPECTIVE
     //m_size{ _size.x / Configurator::viewPortSize().x * Configurator::vpRatioXY(), _size.y / Configurator::viewPortSize().y }
//#else
     m_size{ _size.x, _size.y }
//#endif
{
   updatePosArray();

   glGenBuffers(1, &m_posBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(m_posArray), m_posArray, GL_DYNAMIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Transformable& Transformable::rotate(float _angle)
{
   while(_angle > 360.f)
      _angle -= 360.f;
   m_rotation += _angle;
   m_transform.rotate(_angle);
   return *this;
}

Transformable& Transformable::setRotation(float _angle)
{
   while(_angle > 360.f)
      _angle -= 360.f;
   m_rotation = _angle;
   m_transform.setRotation(_angle);
   return *this;
}

Transformable& Transformable::move(glm::vec2 _offset)
{
   m_position += _offset;
/*
#ifdef PERSPECTIVE
   _offset = Configurator::processCoords(_offset);
#endif
*/
   m_transform.move(_offset);
   return *this;
}

Transformable& Transformable::setSize(glm::vec2 _size)
{
   glm::vec2 origin = getOrigin();
   m_size = _size;
   setOrigin(origin);

   updatePosArray();
   uploadPosArray();

   return *this;
}

Transformable& Transformable::setPosition(glm::vec2 _pos)
{
   m_position = _pos;
/*
#ifdef PERSPECTIVE
   _pos = Configurator::processCoords(_pos);
#endif
*/
   m_transform.setPosition(_pos);
   return *this;
}

Transformable& Transformable::setScale(glm::vec2 _scale)
{
   m_scale = _scale;
   m_transform.setScale(_scale);
   return *this;
}

Transformable& Transformable::setOrigin(glm::vec2 _origin)
{
   m_transform.origin = _origin * m_size;
   setRotation(m_rotation);
   setPosition(m_position);
   return *this;
}

void Transformable::updatePosArray()
{
   m_posArray[0] = glm::vec2(0.f, 0.f);
   m_posArray[1] = glm::vec2(m_size.x, 0.f);
   m_posArray[2] = glm::vec2(m_size.x, m_size.y);
   m_posArray[3] = glm::vec2(0.f, m_size.y);
}

void Transformable::uploadPosArray()
{
   glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_posArray), m_posArray);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // ns
