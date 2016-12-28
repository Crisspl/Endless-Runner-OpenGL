#ifndef FHL_RENDERCONF_H
#define FHL_RENDERCONF_H

#include "Texture.h"
#include "Transform.h"

namespace fhl
{

	struct RenderConf
	{
		RenderConf(const Transform & _transform, Texture * _texture);
		RenderConf(const Transform & _t);
		RenderConf(Texture * _t);
		RenderConf();

		RenderConf & operator+=(const Transform & _t);
		//DrawConf & operator+=(Texture * const _t);

		bool operator==(const RenderConf & _other) const;
		bool operator!=(const RenderConf & _other) const;

		Transform transform;

		static RenderConf Default;
	};

} // ns

#endif // FHL_RENDERCONF_H
