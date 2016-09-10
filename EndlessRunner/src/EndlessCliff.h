#ifndef ENDLESSCLIFF_H
#define ENDLESSCLIFF_H

#include "Graphics/Model.h"
#include "Graphics/DrawFuncs.h"

class EndlessCliff
	: public fhl::Drawable
{
public:
	EndlessCliff();

	void draw(const fhl::DrawConf &) const override;
	void update(float _dt);
	void setLights(std::vector<fhl::Light> & _lights);

private:
	fhl::Model m_model;
};

#endif // ENDLESSCLIFF_H
