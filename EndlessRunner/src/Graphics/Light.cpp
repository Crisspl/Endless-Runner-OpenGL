#include "Light.h"

namespace fhl
{

	 Light::Light()
		 : direction{0, 0, -1},
			color(Color::White),
			cutOffAngle(30.f),
			illuminance(1.f),
			type(Directional)
	 { }

} // ns
