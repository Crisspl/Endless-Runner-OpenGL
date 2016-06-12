#pragma once

#include <glm/glm.hpp>
#include <array>

namespace ut{

struct Projection
{
   bool overlap(Projection _p)
   {
      return (( min > _p.min && min < _p.max) || ( max < _p.max && max > _p.min));
   }

   float min, max;
};

class Rect
{
   using Tverts = std::array<glm::vec2, 4>;

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
   Rect(glm::vec2 _botLeft, glm::vec2 _size);
   virtual ~Rect() { }

protected:
   explicit Rect(glm::vec2 _size);

public:
   virtual bool contains(glm::vec2 _p) const;
   virtual bool intersects(const Rect& _rect) const;

   glm::vec2 operator[](unsigned _i) const { return m_verts[_i]; }
   glm::vec2 botLeft() const { return m_verts[BL]; }
   glm::vec2 getSize() const { return m_verts[UR] - m_verts[BL]; }
   Projection project(glm::vec2 _axis) const;

   virtual Rect& addWidth(float _width);
   virtual Rect& addHeight(float _height);
   virtual Rect& move(glm::vec2 _offset);

   virtual const std::array<glm::vec2, 2>& getAxes() const { return s_axes; }

public:
   float width, height;

protected:
   Tverts m_verts;

private:
   static std::array<glm::vec2, 2> s_axes;
};

} //ns
