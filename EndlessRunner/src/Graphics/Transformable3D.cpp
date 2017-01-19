#include "Transformable3D.h"
#include "Configurator.h"

namespace fhl
{

	 Transformable3D::Transformable3D()
		 : m_rotation{ 0.f, Vec3f(1.f) },
			m_position(0.f),
			m_scale(1.f),
		   m_transformChanged(true),
		   m_mvpChanged(true)
	 { }

	 Transformable3D & Transformable3D::rotate(float _angle, const Vec3f & _axis)
	 {
		 m_transformChanged = m_mvpChanged = true;
		 while(_angle >= 360.f)
			 _angle -= 360.f;

		 m_rotation.angle += _angle;
		 /* TODO update rotation axis (Quaternion) */
		 return *this;
	 }

	 Transformable3D & Transformable3D::setRotation(float _angle, const Vec3f & _axis)
	 {
		 m_transformChanged = m_mvpChanged = true;
		 while(_angle >= 360.f)
			 _angle -= 360.f;

		 m_rotation.angle = _angle;
		 m_rotation.axis = _axis;
		 return *this;
	 }

	 Transformable3D & Transformable3D::move(const Vec3f & _offset)
	 {
		 return setPosition(m_position + _offset);
	 }

	 Transformable3D & Transformable3D::setPosition(const Vec3f & _pos)
	 {
		 m_transformChanged = m_mvpChanged = true;
		 m_position = _pos;
		 return *this;
	 }

	 Transformable3D & Transformable3D::scale(const Vec3f & _scale)
	 {
		  return setScale(m_scale * _scale);
	 }

	 Transformable3D & Transformable3D::setScale(const Vec3f & _scale)
	 {
		 m_transformChanged = m_mvpChanged = true;
		 m_scale = _scale;
		 return *this;
	 }

	 Mat4 Transformable3D::getTransform() const
	 {
		  if (m_transformChanged)
		  {
				m_transformChanged = false;
				return
					 m_transform =
					 Mat4::scale(m_scale) *
					 Mat4::translate(m_position / m_scale) *
					 Mat4::rotate(m_rotation.angle, m_rotation.axis);
		  }
		  else return m_transform;
	 }

	 Mat4 Transformable3D::getMVP() const
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
