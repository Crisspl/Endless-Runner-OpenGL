#include "Transformable.h"

namespace fhl
{

Transformable::Transformable()
   : m_rotation(0.f),
     m_position(0.f, 0.f),
     m_scale(1.f, 1.f)
{
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

Transformable& Transformable::move(Vec2f _offset)
{
   m_position += _offset;
   m_transform.move(_offset);
   return *this;
}

Transformable& Transformable::setPosition(Vec2f _pos)
{
   m_position = _pos;
   m_transform.setPosition(_pos);
   return *this;
}

Transformable& Transformable::setScale(Vec2f _scale)
{
   m_scale = _scale;
   m_transform.setScale(_scale);
   return *this;
}

Transformable& Transformable::setOrigin(Vec2f _origin)
{
   m_transform.origin = _origin;
   setRotation(m_rotation);
   setPosition(m_position);
   return *this;
}

TransformData Transformable::getTransformData() const
{
   return {
            m_position - m_transform.origin,
            m_scale,
            m_transform.origin,
            m_rotation
          };
}

} // ns
