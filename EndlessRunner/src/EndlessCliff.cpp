#include "EndlessCliff.h"

EndlessCliff::EndlessCliff()
	: //m_model("Resources/cliff/Cliff_new.obj")
	m_model("Resources/nano/nanosuit.obj")
{
	m_model.setScale(glm::vec3(120.f));
	m_model.setPosition({ m_model.getScaledSize().x / 2.f + 200.f, 80.f, -1000});
	m_model.move({ -900, -1100, 0 });
}

void EndlessCliff::draw(const fhl::DrawConf &) const
{
	fhl::draw(m_model);
	fhl::DrawConf conf;
	conf += m_model.getTransform().move({ m_model.getScaledSize().x / 2, 0, 0 });
	fhl::draw(m_model, conf);
}

void EndlessCliff::update(float _dt)
{
	//m_model.move({ -_dt * 60, 0, 0 });
}

void EndlessCliff::setLights(std::vector<fhl::Light>& _lights)
{
	m_model.setLights(_lights);
}
