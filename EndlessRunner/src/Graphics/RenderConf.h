#ifndef FHL_RENDERCONF_H
#define FHL_RENDERCONF_H

#include "Texture.h"
#include "Transformable.h"
#include "Light.h"

#include <list>

namespace fhl
{

	struct RenderConf
	{
		  RenderConf(const TransformMatrices & _tm = {}, const Texture * _texture = nullptr, const std::list<Light> _lights = {});
		  RenderConf(const Texture * _t);
		  RenderConf(const std::list<Light> & _lights);

		  RenderConf & operator+=(const TransformMatrices & _tm);
		  RenderConf & operator+=(const Texture * _t);
		  RenderConf & operator+=(const std::list<Light> & _lights);

		  bool operator==(const RenderConf & _other) const;
		  bool operator!=(const RenderConf & _other) const;

		  TransformMatrices matrices;
		  const Texture * texture;
		  std::list<Light> lights;

		  static RenderConf Default;
	};

} // ns

#endif // FHL_RENDERCONF_H
