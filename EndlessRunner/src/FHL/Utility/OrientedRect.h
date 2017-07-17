#ifndef FHL_ORIENTEDRECT_H
#define FHL_ORIENTEDRECT_H

#include <vector>

#include <FHL/Utility/Rect.h>
#include <FHL/Graphics/Transformable.h>

namespace fhl
{

	class OrientedRect : public Rect
	{
	public:
		OrientedRect(const Vec2f & _size, const TransformData & _data);
		OrientedRect(const Vec2f & _botLeft, const Vec2f & _size, const Vec2f & _origin, float _rot);

		bool contains(const Vec2f & _p) const override;
		bool intersects(const Rect & _rect) const override;

		Rect & addWidth(float _width) override;
		Rect & addHeight(float _height) override;
		Rect & move(const Vec2f & _offset) override;

		const std::array<Vec2f, 2> & getAxes() const override { return m_axes; }

	private:
		void applyTransformData(const TransformData & _data);
		void rotate(const Vec2f & _ori, float _angle);
		void calcAxes();

	private:
		std::array<Vec2f, 2> m_axes;
		float m_radAngle;
	};


}

#endif