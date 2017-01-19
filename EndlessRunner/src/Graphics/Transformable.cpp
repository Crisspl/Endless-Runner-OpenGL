#include "Transformable.h"
#include "Configurator.h"

namespace fhl
{

	 Transformable::Transformable()
		 : m_rotation(0.f),
			m_position(0.f, 0.f),
			m_scale(1.f, 1.f),
		   m_transformChanged(true),
		   m_mvpChanged(true)
	 {
	 }

	 Transformable & Transformable::rotate(float _angle)
	 {
			return setRotation(m_rotation + _angle);
	 }

	 Transformable & Transformable::setRotation(float _angle)
	 {
		  m_transformChanged = m_mvpChanged = true;
		  while(_angle >= 360.f)
				_angle -= 360.f;

		  m_rotation = _angle;
		  return *this;
	 }

	 Transformable & Transformable::move(const Vec2f & _offset)
	 { 
		  return setPosition(m_position + _offset);
	 }

	 Transformable & Transformable::setPosition(const Vec2f & _pos)
	 {
		  m_transformChanged = m_mvpChanged = true;
		  m_position = _pos; 
		  return *this;
	 }

	 Transformable & Transformable::scale(const Vec2f & _scale)
	 {
		  return setScale(m_scale * _scale); 
	 }

	 Transformable & Transformable::setScale(const Vec2f & _scale)
	 { 
		  m_transformChanged = m_mvpChanged = true;
		  m_scale = _scale; 
		  return *this; 
	 }

	 Transformable & Transformable::setOrigin(const Vec2f & _origin)
	 { 
		  m_transformChanged = m_mvpChanged = true;
		  m_origin = _origin; 
		  return *this; 
	 }

	 TransformData Transformable::getTransformData() const
	 {
		 return {
					 m_position - m_origin,
					 m_scale,
					 m_origin,
					 m_rotation
				  };
	 }

	 Mat4 Transformable::getTransform() const
	 {
		  if (m_transformChanged)
		  {
				m_transformChanged = false;
				return
					 m_transform =
					 Mat4::scale(Vec3f(m_scale, 1)) *
					 Mat4::translate(Vec3f(m_position - m_origin, 0) / Vec3f(m_scale, 1)) *
					 Mat4::translate(Vec3f(m_origin, 0)) *
					 Mat4::rotate(m_rotation, { 0, 0, 1 }) *
					 Mat4::translate(Vec3f(-m_origin, 0));
		  }
		  else return m_transform;
	 }

	 Mat4 Transformable::getMVP() const
	 {
		  if (m_mvpChanged)
		  {
				m_mvpChanged = false;
				return
					 m_mvp =
					 Configurator::projection() *
					 Configurator::view() *
					 getTransform();
		  }
		  else return m_mvp;
	 }

} // ns
