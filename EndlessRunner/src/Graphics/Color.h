#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <initializer_list>
#include "../Utility/Debug.h"

namespace fhl
{

struct Color
{
   Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 1.f);
   Color(glm::vec4 _color);
   Color(glm::vec3 _color);
   Color(std::initializer_list<float> _rgba);

   glm::vec4 asVec4() const { return color; }

   float operator[](size_t _i) const { return rgba[_i]; }
   float & operator[](size_t _i) { return rgba[_i]; }

   union
   {
	   glm::vec4 color;
	   float rgba[4];
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
