#include "OrientedRect.h"

#include "../Graphics/Transformable.h"

namespace fhl
{

	 OrientedRect::OrientedRect(Vec2f _size, fhl::TransformData _data)
		 : Rect(_size),
			m_radAngle(0)
	 {
		 applyTransformData(_data);
	 }

	 OrientedRect::OrientedRect(Vec2f _botLeft, Vec2f _size, Vec2f _origin, float _rot)
		 : OrientedRect(_size, { _botLeft, {1, 1}, _origin, _rot })
	 {
	 }

	 bool OrientedRect::contains(Vec2f _p) const
	 {
		 for(short i = 0; i < 2; i++)
		 {
			 float dot = m_axes[i].dot(_p);
			 Projection p1 = { dot, dot };
			 Projection p2 = project(m_axes[i]);
			 if(!p1.overlap(p2) && !p2.overlap(p1))
				 return false;
		 }
		 return true;
	 }

	 bool OrientedRect::intersects(const Rect& _rect) const
	 {
		 std::vector<Vec2f> axes;

		 axes.insert(axes.begin(), m_axes.begin(), m_axes.end());
		 axes.insert(axes.begin(), _rect.getAxes().begin(), _rect.getAxes().end());

		 for(const Vec2f& axe : axes)
		 {
			 Projection p1 = this->project(axe);
			 Projection p2 = _rect.project(axe);

			 if(!p1.overlap(p2) && !p2.overlap(p1))
				 return false;
		 }

		 return true;
	 }

	 Rect& OrientedRect::addWidth(float _width)
	 {
		 width += _width;
		 Vec2f offset = { _width * cos(m_radAngle), _width * sin(m_radAngle) };
		 m_verts[BR] += offset;
		 m_verts[UR] += offset;
		 return *this;
	 }

	 Rect& OrientedRect::addHeight(float _height)
	 {
		 height += _height;
		 float angle = m_radAngle + toRadians(90.f);
		 Vec2f offset = { _height * cos(angle), _height * sin(angle) };
		 m_verts[UL] += offset;
		 m_verts[UR] += offset;
		 return *this;
	 }

	 Rect& OrientedRect::move(Vec2f _offset)
	 {
		 Vec2f x = { _offset.x * cos(m_radAngle), _offset.x * sin(m_radAngle) };
		 float angle = m_radAngle + toRadians(90.f);
		 Vec2f y = { _offset.y * cos(angle), _offset.y * sin(angle) };

		 Vec2f offset = x + y;

		 return Rect::move(offset);
	 }

	 void OrientedRect::applyTransformData(const fhl::TransformData& _data)
	 {
		 rotate(_data.origin, _data.rotation);
		 Rect::move(_data.botLeft);

		 m_radAngle = toRadians(_data.rotation);

		 calcAxes();
	 }

	 void OrientedRect::rotate(Vec2f _ori, float _angle)
	 {
		 float angle = toRadians(_angle);
		 float s = sin(angle);
		 float c = cos(angle);

		 move(-_ori);

		 for(Vec2f& vert : m_verts)
		 {
			 Vec2f nu;
			 nu.x = vert.x * c - vert.y * s;
			 nu.y = vert.x * s + vert.y * c;
			 vert = nu;
		 }

		 move(_ori);
	 }

	 void OrientedRect::calcAxes()
	 {
		 for(short i = 0; i < 2; i++)
		 {
			 Vec2f edge = m_verts[i] - m_verts[i + 1];
			 m_axes[i] = Vec2f(edge.y, -edge.x).normalized();
		 }
	 }

} // ns
