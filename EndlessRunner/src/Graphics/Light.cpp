#include "Light.h"

namespace gr
{

Light::Light()
   : direction{0, 0, -1},
     color(Color::White),
     cutOffAngle(30.f),
     illuminance(1.f),
     type(Directional)
{ }

} // ns
