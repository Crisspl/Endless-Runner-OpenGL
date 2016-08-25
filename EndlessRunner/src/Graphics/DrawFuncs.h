#ifndef DRAWFUNCS_H
#define DRAWFUNCS_H

#include "Drawable.h"
#include "DrawConf.h"

namespace fhl
{

	void draw(const Drawable & _drawable, const DrawConf & _conf = DrawConf::Default);

} // ns

#endif // DRAWFUNCS_H
