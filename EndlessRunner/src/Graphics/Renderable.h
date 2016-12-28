#ifndef FHL_RENDERABLE_H
#define FHL_RENDERABLE_H

#include "RenderConf.h"

namespace fhl
{

	 class Renderable
	 {
		 friend void render(const Renderable &, const RenderConf &);

	 public:
		 virtual ~Renderable() { }

	 protected:
		 virtual void render(const RenderConf &) const = 0;
	 };

} // ns

#endif // FHL_RENDERABLE_H
