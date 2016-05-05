#include "Litable.h"

namespace gr
{

Litable::Litable(Shader& _shader)
   : WithShader(_shader)
{
}

void Litable::setLight(const Light& _light)
{
   m_shader->setLight("light", _light);
}

void Litable::setLights(const std::vector<Light>& _lights)
{
   m_shader->setLights("light", _lights);
}

} // ns
