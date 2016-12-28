#ifndef ENDLESSCLIFF_H
#define ENDLESSCLIFF_H

#include "Graphics/Model.h"
#include "Graphics/RenderFuncs.h"

class EndlessCliff
	: public fhl::Renderable
{
public:
	EndlessCliff();

	void render(const fhl::RenderConf &) const override;
	void update(float _dt);
	void setLights(std::vector<fhl::Light> & _lights);

private:
	fhl::Model m_model;
};

#endif // ENDLESSCLIFF_H
