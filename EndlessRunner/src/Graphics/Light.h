#ifndef FHL_LIGHT_H
#define FHL_LIGHT_H

#include "Color.h"

namespace fhl
{

	 struct Light
	 {
		  enum Type
		  {
				Infinite = 0,
				Point,
				Spot
		  };

		  Light(Type _t = Infinite);

		  static Light infinite(Vec3f _dir, Color _color = Color::White, float _illu = 1.f);
		  static Light point(Vec3f _pos, float _linear = 0.045f, float _qudratic = 0.0075f, Color _color = Color::White, float _illu = 1.f);
		  static Light spot(Vec3f _pos, Vec3f _dir = { 0, 0, -1 }, float _cutOff = 30.f, Color _color = Color::White, float _illu = 1.f);

		  Vec3f position, direction;
		  Color color;
		  float linear, quadratic;
		  float cutOffAngle;
		  float illuminance;
		  Type type;
	 };

} // ns

#endif // FHL_LIGHT_H
