#include "Light.h"

namespace fhl
{

	 Light::Light(Type _t)
		 : direction{0, 0, -1},
			color(Color::White),
			cutOffAngle(30.f),
			illuminance(1.f),
			type(_t)
	 { }

	 Light Light::infinite(Vec3f _dir, Color _color, float _illu)
	 {
		  Light light(Infinite);
		  light.direction = _dir;
		  light.color = _color;
		  light.illuminance = _illu;

		  return light;
	 }

	 Light Light::point(Vec3f _pos, float _linear, float _qudratic, Color _color, float _illu)
	 {
		  Light light(Point);
		  light.position = _pos;
		  light.linear = _linear;
		  light.quadratic = _qudratic;
		  light.color = _color;
		  light.illuminance = _illu;

		  return light;
	 }

	 Light Light::spot(Vec3f _pos, Vec3f _dir, float _cutOff, Color _color, float _illu)
	 {
		  Light light(Spot);
		  light.position = _pos;
		  light.direction = _dir;
		  light.cutOffAngle = _cutOff;
		  light.color = _color;
		  light.illuminance = _illu;

		  return light;
	 }

} // ns
