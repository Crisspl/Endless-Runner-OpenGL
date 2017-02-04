#include "Transformable3D.h"
#include "Configurator.h"

namespace fhl
{

	 Transformable3D::Transformable3D()
		 : m_rotation(),
			m_position(0.f),
			m_scale(1.f),
		   m_transformChanged(true),
		   m_mvpChanged(true)
	 { }

	 Transformable3D & Transformable3D::rotate(float _angle, const Vec3f & _axis)
	 {
		 m_transformChanged = m_mvpChanged = true;

		 m_rotation = Quaternion(_axis, _angle) * m_rotation;
		 return *this;
	 }

	 Transformable3D & Transformable3D::setRotation(float _angle, const Vec3f & _axis)
	 {
		 m_transformChanged = m_mvpChanged = true;

		 m_rotation = Quaternion(_axis, _angle);
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

	 Transformable3D & Transformable3D::setOrigin(Vec3f _origin)
	 {
		  m_transformChanged = m_mvpChanged = true;
		  m_origin = _origin;
		  return *this;
	 }

	 Mat4 Transformable3D::getTransform() const
	 {
		  if (m_transformChanged)
		  {
				m_transformChanged = false;
				return
					 m_transform = createTransformMatrix(m_position, m_scale, m_origin, m_rotation);
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

	 TransformMatrices Transformable3D::createTransformMatrices(const Vec3f & _pos, const Vec3f & _scale, const Vec3f & _origin, const Quaternion & _rotation)
	 {
		  Mat4 transform = createTransformMatrix(_pos, _scale, _origin, _rotation);
		  return
		  {
				transform,
				Configurator::projection() * Configurator::view() * transform
		  };
	 }

	 TransformMatrices Transformable3D::calcModifiedTransformMatrices(const Vec3f & _mvOffset, const Vec3f & _scaleMlt, const Quaternion & _rotation) const
	 {
		  return createTransformMatrices(m_position + _mvOffset, m_scale * _scaleMlt, m_origin, _rotation * m_rotation);
	 }

	 Mat4 Transformable3D::createTransformMatrix(const Vec3f & _pos, const Vec3f & _scale, const Vec3f & _origin, const Quaternion & _rotation)
	 {
		  return
				Mat4::scale(_scale) *
				Mat4::translate((_pos - _origin) / _scale) *
				Mat4::translate(_origin) *
				_rotation.toMat4() *
				Mat4::translate(-_origin);
	 }


} // ns
