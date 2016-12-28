#include "RenderConf.h"

namespace fhl
{

	 RenderConf RenderConf::Default;

	 RenderConf::RenderConf(const Transform & _transform, Texture * _texture)
		 : transform(_transform)
		  // texture(_texture)
	 {
	 }

	 RenderConf::RenderConf(const Transform & _t)
		 : RenderConf(_t, nullptr)
	 {
	 }

	 RenderConf::RenderConf(Texture * _t)
		 : RenderConf(Transform(), _t)
	 {
	 }

	 RenderConf::RenderConf()
		 : RenderConf(Transform(), nullptr)
	 {
	 }

	 RenderConf & RenderConf::operator+=(const Transform & _t)
	 {
		 transform = _t;
		 return *this;
	 }
	 /*
	 DrawConf & DrawConf::operator+=(Texture * const _t)
	 {
		 texture = _t;
		 return *this;
	 }
	 */
	 bool RenderConf::operator==(const RenderConf & _other) const
	 {
		 if (this == &_other) 
			 return true;
		 return transform == _other.transform;
	 }

	 bool RenderConf::operator!=(const RenderConf & _other) const
	 {
		 return !(*this == _other);
	 }


} // ns