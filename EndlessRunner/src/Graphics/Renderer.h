#ifndef FHL_RENDERFUNCS_H
#define FHL_RENDERFUNCS_H

#include "Renderable.h"
#include "RenderConf.h"
#include "Color.h"

namespace fhl
{
	class Renderer
	{
		Renderer() = delete;

	public:
		static void render(const Renderable & _drawable, const RenderConf & _conf = RenderConf::Default);
		static void clearColor(Color _color = Color::Black);
	};

} // ns

#endif // FHL_RENDERFUNCS_H
