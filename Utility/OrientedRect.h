#pragma once

#include <array>
#include <vector>

#include "Rect.h"
#include "../Graphics/Sprite.h"

namespace gr { class TransformData; class Sprite; }

namespace ut
{

class OrientedRect
   : public Rect
{
   friend OrientedRect gr::Sprite::getOBB() const;

public:
   explicit OrientedRect(glm::vec2 _size);
   OrientedRect(glm::vec2 _size, gr::TransformData _data);

   const std::array<glm::vec2, 2>& getAxes() const { return m_axes; }

   bool contains(glm::vec2 _p) const override;
   bool intersects(const Rect& _rect) const override;

   Rect& addWidth(float _width) override;
   Rect& addHeight(float _height) override;
   Rect& move(glm::vec2 _offset) override;

private:
   void applyTransformData(const gr::TransformData& _data);
   void rotate(glm::vec2 _ori, float _angle);
   void calcAxes();

private:
   std::array<glm::vec2, 2> m_axes;
   float m_radAngle;
};


} // ns
