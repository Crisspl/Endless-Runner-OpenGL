#ifndef LITABLE_H
#define LITABLE_H

#include "WithShader.h"
#include "Light.h"

namespace fhl
{

class Litable
   : public WithShader /* Make it virtual inheritance if comes more children classes of WithShader */
{                      /* and add WithShader ctor calls in Sprite, ColoredRect, etc. */
public:
   Litable(Shader& _shader);
   virtual ~Litable() { }

   virtual void setLight(const Light& _light);
   virtual void setLights(const std::initializer_list<std::reference_wrapper<Light>>& _lights);
};

}

#endif // LITABLE_H
