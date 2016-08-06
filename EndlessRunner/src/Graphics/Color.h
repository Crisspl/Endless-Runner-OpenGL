#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <algorithm>

namespace gr
{

struct Color
{
   Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 255.f);
   Color(glm::vec4 _color);

   glm::vec4 asNormalizedVec4() const { return m_color; }
   glm::vec4 asVec4() const { return m_color * 255.f; }

   union
   {
	   glm::vec4 m_color;
	   struct { float r, g, b, a; };
   };

public:
   static const Color White;
   static const Color Black;
   static const Color Red;
   static const Color Green;
   static const Color Blue;
   static const Color Transparent;
};

} // ns

#endif // COLOR_H
