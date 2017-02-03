#ifndef FHL_RECT_H
#define FHL_RECT_H

#include <array>
#include "../Maths/vectors.h"

namespace fhl {

	 struct Projection
	 {
		  bool overlap(Projection _p)
		  {
				return ((min > _p.min && min < _p.max) || (max < _p.max && max > _p.min));
		  }

		  float min, max;
	 };

	 class Rect
	 {
		  using Tverts = std::array<Vec2f, 4>;

	 public:
		  enum VerticlePos /* Note Y axis can be inverted ! */
		  {
				BL, // Bottom-left
				BR, // Bottom-right
				UR, // Upper-right
				UL  // Upper-left
		  };

	 public:
		  Rect();
		  Rect(Vec2f _botLeft, Vec2f _size);
		  explicit Rect(Vec2f _size);
		  virtual ~Rect() { }

	 public:
		  virtual bool contains(Vec2f _p) const;
		  virtual bool intersects(const Rect& _rect) const;

		  Vec2f operator[](unsigned _i) const { return m_verts[_i]; }
		  const Tverts & getVerts() const { return m_verts; }

		  Vec2f botLeft() const { return m_verts[BL]; }
		  Vec2f getSize() const { return m_size; }
		  Projection project(Vec2f _axis) const;

		  virtual Rect & addWidth(float _width);
		  virtual Rect & addHeight(float _height);
		  virtual Rect & move(Vec2f _offset);

		  virtual const std::array<Vec2f, 2> & getAxes() const { return s_axes; }

	 protected:
		  Vec2f m_size;
		  Tverts m_verts;

	 private:
		  static std::array<Vec2f, 2> s_axes;
	 };

} //ns

#endif // FHL_RECT_H