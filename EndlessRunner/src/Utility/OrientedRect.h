#ifndef ORIENTEDRECT_H
#define ORIENTEDRECT_H

#include <vector>

#include "Rect.h"
#include "../Graphics/Sprite.h"

namespace gr { class TransformData; class Sprite; }

namespace ut
{

class OrientedRect
   : public Rect
{
public:
   OrientedRect(glm::vec2 _size, gr::TransformData _data);
   OrientedRect(glm::vec2 _botLeft, glm::vec2 _size, glm::vec2 _origin, float _rot);

   bool contains(glm::vec2 _p) const override;
   bool intersects(const Rect& _rect) const override;

   Rect& addWidth(float _width) override;
   Rect& addHeight(float _height) override;
   Rect& move(glm::vec2 _offset) override;

   const std::array<glm::vec2, 2>& getAxes() const override { return m_axes; }

private:
   void applyTransformData(const gr::TransformData& _data);
   void rotate(glm::vec2 _ori, float _angle);
   void calcAxes();

private:
   std::array<glm::vec2, 2> m_axes;
   float m_radAngle;
};


} // ns

#endif // ORIENTEDRECT_H
