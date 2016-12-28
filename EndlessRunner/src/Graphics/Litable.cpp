#include "Litable.h"

namespace fhl
{

	 Litable::Litable(Shader& _shader)
		 : WithShader(_shader)
	 {
	 }

	 void Litable::setLight(const Light& _light)
	 {
		 m_shader->setLight("light", _light);
	 }

	 void Litable::setLights(const std::initializer_list<std::reference_wrapper<Light>>& _lights)
	 {
		 m_shader->setLights("light", _lights);
	 }

	 void Litable::setLights(std::vector<Light>& _lights)
	 {
		 m_shader->setLights("light", _lights);
	 }

} // ns
