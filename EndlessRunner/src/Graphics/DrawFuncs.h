#ifndef FHL_DRAWFUNCS_H
#define FHL_DRAWFUNCS_H

#include "Drawable.h"
#include "DrawConf.h"

namespace fhl
{

	void draw(const Drawable & _drawable, const DrawConf & _conf = DrawConf::Default);

} // ns

#endif // FHL_DRAWFUNCS_H
