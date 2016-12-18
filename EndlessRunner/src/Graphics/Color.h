#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <initializer_list>
#include "../Utility/Debug.h"
#include "../Maths/Vectors.h"

namespace fhl
{

struct Color
{
   Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 1.f);
   Color(Vec4f _color);
   Color(Vec3f _color);
   Color(std::initializer_list<float> _rgba);

   Vec4f asVec4() const { return color; }

   float operator[](size_t _i) const { return rgba[_i]; }
   float & operator[](size_t _i) { return rgba[_i]; }

   union
   {
	   Vec4f color;
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
