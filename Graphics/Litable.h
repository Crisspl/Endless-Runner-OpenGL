#pragma once

#include <vector>

#include "WithShader.h"
#include "Light.h"

namespace gr
{

class Litable
   : virtual public WithShader
{
public:
   Litable(Shader& _shader);
   virtual ~Litable() { }

   virtual void setLight(const Light& _light);
   virtual void setLights(const std::vector<Light>& _lights);
};

}
