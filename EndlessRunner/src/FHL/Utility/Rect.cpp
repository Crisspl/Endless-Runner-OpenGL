#include <FHL/Utility/Rect.h>

#include <FHL/Graphics/Transformable.h>

namespace fhl
{
	bool Rect::contains(const Vec2f & _p) const
	{
		return (_p.x() < botLeft().x() + m_size.x() && _p.x() > botLeft().x()) && (_p.y() < botLeft().y() + m_size.y() && _p.y() > botLeft().y());
	}

	bool Rect::intersects(const Rect & _rect) const
	{
		for (int i = 0; i < 4; i++)
		{
			if (this->contains(_rect[i]))
				return true;
		}
		return false;
	}

	Projection Rect::project(Vec2f _axis) const
	{
		float min = m_verts[0].dot(_axis);
		float max = min;

		for (short i = 1; i < 4; i++)
		{
			float p = m_verts[i].dot(_axis);
			if (p < min)
				min = p;
			else if (p > max)
				max = p;
		}

		return{ min, max };
	}

	Rect & Rect::addWidth(float _width)
	{
		m_size.x() += _width;
		m_verts[BR].x() += _width;
		m_verts[UR].x() += _width;
		return *this;
	}

	Rect & Rect::addHeight(float _height)
	{
		m_size.y() += _height;
		m_verts[UL].y() += _height;
		m_verts[UR].y() += _height;
		return *this;
	}

	Rect & Rect::move(const Vec2f & _offset)
	{
		for (auto& vert : m_verts)
			vert += _offset;
		return *this;
	}

}