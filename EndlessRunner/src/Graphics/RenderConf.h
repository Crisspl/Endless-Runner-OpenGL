#ifndef FHL_RENDERCONF_H
#define FHL_RENDERCONF_H

#include "Texture.h"
#include "Transformable.h"

namespace fhl
{

	struct RenderConf
	{
		  RenderConf(const TransformMatrices & _tm, Texture * _texture);
		  RenderConf(const TransformMatrices & _tm);
		  RenderConf(Texture * _t);
		  RenderConf();

		  RenderConf & operator+=(const TransformMatrices & _t);
		  //RenderConf & operator+=(Texture * const _t);

		  bool operator==(const RenderConf & _other) const;
		  bool operator!=(const RenderConf & _other) const;

		  TransformMatrices matrices;

		  static RenderConf Default;
	};

} // ns

#endif // FHL_RENDERCONF_H
