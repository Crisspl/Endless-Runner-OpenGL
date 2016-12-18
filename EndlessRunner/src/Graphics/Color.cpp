#include "Color.h"

#include <algorithm>

#define _clamp(n, lo, hi) (std::max(lo, std::min(n, hi)))

namespace fhl
{

const Color Color::White = Color(Vec4f(1.f));
const Color Color::Black;
const Color Color::Red = Color(1.f, 0.f, 0.f);
const Color Color::Green = Color(0.f, 1.f, 0.f);
const Color Color::Blue = Color(0.f, 0.f, 1.f);
const Color Color::Transparent = Color(Vec4f(0.f));

Color::Color(float _r, float _g, float _b, float _a)
	: color{
			_clamp(_r, 0.f, 1.f),
			_clamp(_g, 0.f, 1.f),
			_clamp(_b, 0.f, 1.f),
			_clamp(_a, 0.f, 1.f)
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
	auto it = _rgba.begin();
	for (size_t i = 0; i < 4; i++, it++)
		rgba[i] = _clamp(*it, 0.f, 1.f);
}

#undef _clamp

} // ns
