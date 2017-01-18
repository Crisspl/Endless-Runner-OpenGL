#ifndef FHL_ORIENTEDRECT_H
#define FHL_ORIENTEDRECT_H

#include <vector>

#include "Rect.h"
#include "../Graphics/Sprite.h"

namespace fhl { struct TransformData; class Sprite; }

namespace fhl
{

	 class OrientedRect
		  : public Rect
	 {
	 public:
		  OrientedRect(Vec2f _size, TransformData _data);
		  OrientedRect(Vec2f _botLeft, Vec2f _size, Vec2f _origin, float _rot);

		  bool contains(Vec2f _p) const override;
		  bool intersects(const Rect& _rect) const override;

		  Rect & addWidth(float _width) override;
		  Rect & addHeight(float _height) override;
		  Rect & move(Vec2f _offset) override;

		  const std::array<Vec2f, 2> & getAxes() const override { return m_axes; }

	 private:
		  void applyTransformData(const TransformData & _data);
		  void rotate(Vec2f _ori, float _angle);
		  void calcAxes();

	 private:
		  std::array<Vec2f, 2> m_axes;
		  float m_radAngle;
	 };


} // ns

#endif // FHL_ORIENTEDRECT_H