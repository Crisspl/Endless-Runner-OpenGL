#ifndef FHL_RECT_H
#define FHL_RECT_H

#include <array>

#include <FHL/Maths/vectors.h>

namespace fhl {

	 struct Projection
	 {
		  constexpr bool overlap(const Projection & _p)
		  {
				return ((min > _p.min && min < _p.max) || (max < _p.max && max > _p.min));
		  }
		  float min, max;
	 };

	 class Rect
	 {
		 using Verts_t = std::array<Vec2f, 4>;

	 public:
		 enum VerticlePos /* Note Y axis can be inverted ! */
		 {
			 BL, // Bottom-left
			 BR, // Bottom-right
			 UR, // Upper-right
			 UL  // Upper-left
		 };

	 public:
		 Rect() : m_size{ Vec2f::zero() } {}
		 Rect(const Vec2f & _botLeft, const Vec2f & _size) :
			 m_size{ _size },
			 m_verts{ { _botLeft, _botLeft + Vec2f(_size.x(), 0), _botLeft + _size, _botLeft + Vec2f(0, _size.y()) } } {}
		 explicit Rect(const Vec2f & _size) : Rect(Vec2f::zero(), _size) {}
		 virtual ~Rect() = default;

	 public:
		 virtual bool contains(const Vec2f & _p) const;
		 virtual bool intersects(const Rect& _rect) const;

		 Vec2f operator[](unsigned _i) const { return m_verts[_i]; }
		 const Verts_t & getVerts() const { return m_verts; }

		 Vec2f botLeft() const { return m_verts[BL]; }
		 Vec2f getSize() const { return m_size; }
		 Projection project(Vec2f _axis) const;

		 virtual Rect & addWidth(float _width);
		 virtual Rect & addHeight(float _height);
		 virtual Rect & move(const Vec2f & _offset);

		 virtual const std::array<Vec2f, 2> & getAxes() const { return s_axes; }

	 protected:
		 Vec2f m_size;
		 Verts_t m_verts;

	 private:
		 constexpr static std::array<Vec2f, 2> s_axes{ { { 1, 0 }, { 0, 1 } } };
	 };

}

#endif