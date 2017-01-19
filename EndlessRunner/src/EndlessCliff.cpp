#include "EndlessCliff.h"

EndlessCliff::EndlessCliff()
	: m_model("Resources/cliff/Cliff_new.obj")
{
	m_model.setScale(fhl::Vec3f(12.f));
	m_model.setPosition({ m_model.getScaledSize().x / 2.f - 50.f, 80.f, 0});
	m_model.setShader(fhl::UsingShader::Light);
}

void EndlessCliff::render(const fhl::RenderConf &) const
{
	fhl::render(m_model);
	//fhl::RenderConf conf;
	//fhl::render(m_model, conf);
}

void EndlessCliff::update(float _dt)
{
	m_model.move({ -_dt * 60, 0, 0 });
}

void EndlessCliff::setLights(std::vector<fhl::Light>& _lights)
{
	m_model.setLights(_lights.begin(), _lights.end());
}
