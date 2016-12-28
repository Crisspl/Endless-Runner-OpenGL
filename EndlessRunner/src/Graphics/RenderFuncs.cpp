#include "RenderFuncs.h"

namespace fhl
{

	 void render(const Renderable & _drawable, const RenderConf & _conf)
	 {
		  _drawable.render(_conf);
	 }

}
