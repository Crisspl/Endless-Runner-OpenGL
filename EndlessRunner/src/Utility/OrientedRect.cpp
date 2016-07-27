#include "OrientedRect.h"

#include "../Graphics/Transformable.h"

namespace ut
{

OrientedRect::OrientedRect(glm::vec2 _size, gr::TransformData _data)
   : Rect(_size),
     m_radAngle(0)
{
   applyTransformData(_data);
}

OrientedRect::OrientedRect(glm::vec2 _botLeft, glm::vec2 _size, glm::vec2 _origin, float _rot)
   : OrientedRect(_size, { _botLeft, {1, 1}, _origin, _rot })
{
}

bool OrientedRect::contains(glm::vec2 _p) const
{
   for(short i = 0; i < 2; i++)
   {
      float dot = glm::dot(m_axes[i], _p);
      Projection p1 = { dot, dot };
      Projection p2 = project(m_axes[i]);
      if(!p1.overlap(p2) && !p2.overlap(p1))
         return false;
   }
   return true;
}

bool OrientedRect::intersects(const Rect& _rect) const
{
   std::vector<glm::vec2> axes;

   axes.insert(axes.begin(), m_axes.begin(), m_axes.end());
   axes.insert(axes.begin(), _rect.getAxes().begin(), _rect.getAxes().end());

   for(const glm::vec2& axe : axes)
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
   glm::vec2 offset = { _width * cos(m_radAngle), _width * sin(m_radAngle) };
   m_verts[BR] += offset;
   m_verts[UR] += offset;
   return *this;
}

Rect& OrientedRect::addHeight(float _height)
{
   height += _height;
   float angle = m_radAngle + glm::radians(90.f);
   glm::vec2 offset = { _height * cos(angle), _height * sin(angle) };
   m_verts[UL] += offset;
   m_verts[UR] += offset;
   return *this;
}

Rect& OrientedRect::move(glm::vec2 _offset)
{
   glm::vec2 x = { _offset.x * cos(m_radAngle), _offset.x * sin(m_radAngle) };
   float angle = m_radAngle + glm::radians(90.f);
   glm::vec2 y = { _offset.y * cos(angle), _offset.y * sin(angle) };

   glm::vec2 offset = x + y;

   return Rect::move(offset);
}

void OrientedRect::applyTransformData(const gr::TransformData& _data)
{
   rotate(_data.origin, _data.rotation);
   Rect::move(_data.botLeft);

   m_radAngle = glm::radians(_data.rotation);

   calcAxes();
}

void OrientedRect::rotate(glm::vec2 _ori, float _angle)
{
   float angle = glm::radians(_angle);
   float s = sin(angle);
   float c = cos(angle);

   move(-_ori);

   for(glm::vec2& vert : m_verts)
   {
      glm::vec2 nu;
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
      glm::vec2 edge = m_verts[i] - m_verts[i + 1];
      m_axes[i] = glm::normalize(glm::vec2(edge.y, -edge.x));
   }
}

} // ns
