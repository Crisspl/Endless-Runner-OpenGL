#include "Color.h"

namespace gr
{

const Color Color::White = Color(glm::vec4(255.f));
const Color Color::Black;
const Color Color::Red = Color(255.f, 0.f, 0.f);
const Color Color::Green = Color(0.f, 255.f, 0.f);
const Color Color::Blue = Color(0.f, 0.f, 255.f);
const Color Color::Transparent = Color(glm::vec4(0.f));

Color::Color(glm::vec4 _color)
   : Color(_color.x, _color.y, _color.z, _color.w)
{
}

Color::Color(float _r, float _g, float _b, float _a)
   : m_color(glm::vec4(std::min(_r, 255.f),
                       std::min(_g, 255.f),
                       std::min(_b, 255.f),
                       std::min(_a, 255.f)
                  ) / 255.f)
{
}

} // ns
