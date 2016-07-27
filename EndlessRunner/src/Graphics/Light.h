#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Color.h"

namespace gr
{

struct Light
{
   enum Type
   {
      Directional = 0,
      Point,
      Spot
   };

   Light();

   glm::vec3 position, direction;
   Color color;
   float linear, quadratic;
   float cutOffAngle;
   float illuminance;
   Type type;
};

} // ns

#endif // LIGHT_H
