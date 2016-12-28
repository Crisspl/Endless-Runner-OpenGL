#ifndef FHL_RENDERFUNCS_H
#define FHL_RENDERFUNCS_H

#include "Renderable.h"
#include "RenderConf.h"

namespace fhl
{

	 void render(const Renderable & _drawable, const RenderConf & _conf = RenderConf::Default);

} // ns

#endif // FHL_RENDERFUNCS_H
