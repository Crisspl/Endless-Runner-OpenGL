#ifndef DRAWCONF_H
#define DRAWCONF_H

#include "Texture.h"
#include "Transform.h"

namespace fhl
{

	struct DrawConf
	{
		DrawConf(const Transform & _transform, Texture * _texture);
		DrawConf(const Transform & _t);
		DrawConf(Texture * _t);
		DrawConf();

		DrawConf & operator+=(const Transform & _t);
		//DrawConf & operator+=(Texture * const _t);

		bool operator==(const DrawConf & _other) const;
		bool operator!=(const DrawConf & _other) const;

		Transform transform;

		static DrawConf Default;
	};

} // ns

#endif // DRAWCONF_H
