#include "RenderConf.h"

namespace fhl
{

	 RenderConf RenderConf::Default;

	 RenderConf::RenderConf(const TransformMatrices & _tm, Texture * _texture)
		 : matrices(_tm)
		  // texture(_texture)
	 {
	 }

	 RenderConf::RenderConf(const TransformMatrices & _tm)
		 : RenderConf(_tm, nullptr)
	 {
	 }

	 RenderConf::RenderConf(Texture * _t)
		  : RenderConf({}, _t)
	 {
	 }

	 RenderConf::RenderConf()
		  : RenderConf({}, nullptr)
	 {
	 }

	 RenderConf & RenderConf::operator+=(const TransformMatrices & _t)
	 {
		 matrices = _t;
		 return *this;
	 }
	 /*
	 RenderConf & RenderConf::operator+=(Texture * const _t)
	 {
		 texture = _t;
		 return *this;
	 }
	 */
	 bool RenderConf::operator==(const RenderConf & _other) const
	 {
		  if (this == &_other) 
				return true;
		  return 
				matrices.transform == _other.matrices.transform &&
				matrices.mvp == _other.matrices.mvp;
	 }

	 bool RenderConf::operator!=(const RenderConf & _other) const
	 {
		 return !(*this == _other);
	 }


} // ns