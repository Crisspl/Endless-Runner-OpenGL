#include "Rect.h"

#include "../Graphics/Transformable.h"

namespace fhl
{

std::array<fhl::Vec2f, 2> Rect::s_axes = {{ {1, 0}, {0, 1} }};

Rect::Rect()
      : width(0.f),
        height(0.f)
{
}

Rect::Rect(fhl::Vec2f _botLeft, fhl::Vec2f _size)
      : width(_size.x),
        height(_size.y),
        m_verts{ {_botLeft, _botLeft + fhl::Vec2f(_size.x, 0), _botLeft + _size, _botLeft + fhl::Vec2f(0, _size.y) } }
{
}

Rect::Rect(fhl::Vec2f _size)
      : Rect({0, 0}, _size)
{
}

bool Rect::contains(fhl::Vec2f _p) const
{
   return (_p.x < botLeft().x + width && _p.x > botLeft().x)
                              &&
          (_p.y < botLeft().y + height && _p.y > botLeft().y);
}

bool Rect::intersects(const Rect& _rect) const
{
   for(short i = 0; i < 4; i++)
   {
      if(this->contains(_rect[i]))
         return true;
   }
   return false;
}

Projection Rect::project(fhl::Vec2f _axis) const
{
   float min = m_verts[0].dot(_axis);
   float max = min;

   for(short i = 1; i < 4; i++)
   {
	  float p = m_verts[i].dot(_axis);
      if(p < min)
         min = p;
      else if(p > max)
         max = p;
   }

   return { min, max };
}

Rect& Rect::addWidth(float _width)
{
   width += _width;
   m_verts[BR].x += _width;
   m_verts[UR].x += _width;
   return *this;
}

Rect& Rect::addHeight(float _height)
{
   height += _height;
   m_verts[UL].y += _height;
   m_verts[UR].y += _height;
   return *this;
}

Rect& Rect::move(fhl::Vec2f _offset)
{
   for(auto& vert : m_verts)
      vert += _offset;
   return *this;
}

} //ns
