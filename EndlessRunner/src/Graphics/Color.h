#ifndef FHL_COLOR_H
#define FHL_COLOR_H

#include <glm/glm.hpp>
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

		  Vec4f asVec4() const { return{ r, g, b, a }; }

		  float operator[](size_t _i) const { return *(&r + _i); }
		  float & operator[](size_t _i) { return *(&r + _i); }

		  float r, g, b, a;

		  static const Color White;
		  static const Color Black;
		  static const Color Red;
		  static const Color Green;
		  static const Color Blue;
		  static const Color Yellow;
		  static const Color Magenta;
		  static const Color Cyan;
		  static const Color Transparent;
	 };

} // ns

#endif // FHL_COLOR_H
