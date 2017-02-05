#include "Color.h"

#include <algorithm>
#include "../Maths/mathsFuncs.h"

namespace fhl
{

	 const Color Color::White = Color(Vec4f::one());
	 const Color Color::Black;
	 const Color Color::Red = Color(1.f, 0.f, 0.f);
	 const Color Color::Green = Color(0.f, 1.f, 0.f);
	 const Color Color::Blue = Color(0.f, 0.f, 1.f);
	 const Color Color::Yellow = Color(1.f, 1.f, 0.f);
	 const Color Color::Magenta = Color(1.f, 0.f, 1.f);
	 const Color Color::Cyan = Color(0.f, 1.f, 1.f);
	 const Color Color::Transparent = Color(Vec4f::zero());

	 Color::Color(float _r, float _g, float _b, float _a)
		 : Color{
				 clamp(_r, 0.f, 1.f),
				 clamp(_g, 0.f, 1.f),
				 clamp(_b, 0.f, 1.f),
				 clamp(_a, 0.f, 1.f)
				 } 
	 {
	 }

	 Color::Color(Vec4f _color)
		 : Color(_color.x, _color.y, _color.z, _color.w)
	 {
	 }

	 Color::Color(Vec3f _color)
		 : Color(Vec4f(_color, 1.f))
	 {
	 }

	 Color::Color(std::initializer_list<float> _rgba)
	 {
		  for (int i = 0; i < 4; i++)
		  {
				if (i <= _rgba.size() - 1)
					 (*this)[i] = clamp(*(_rgba.begin() + i), 0.f, 1.f);
				else
					 (*this)[i] = 1.f;
		  }
	 }

	 bool Color::operator==(const Color & _other) const
	 {
		  return asVec4() == _other.asVec4();
	 }

	 bool Color::operator!=(const Color & _other) const
	 {
		  return !(*this == _other);
	 }

} // ns
