#ifndef FHL_SWIZZLE_H
#define FHL_SWIZZLE_H

#include "vectors.h"

namespace fhl { namespace swizzle
{
	 enum VecDim
	 {
		  X = 0,
		  Y = 1,
		  Z = 2,
		  W = 3
	 };

	 template<VecDim _D0, VecDim _D1, typename _VecT>
	 Vec2<typename _VecT::valueType> get(const _VecT & _v)
	 {
		  static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions,
				"Not enough vector dimensions to get the one(s) demanded");

		  return{ _v[_D0], _v[_D1] };
	 }

	 template<VecDim _D0, VecDim _D1, VecDim _D2, typename _VecT>
	 Vec3<typename _VecT::valueType> get(const _VecT & _v)
	 {
		  static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions && _D2 < _VecT::Dimensions,
				"Not enough vector dimensions to get the one(s) demanded");

		  return Vec3<typename _VecT::valueType>(get<_D0, _D1>(_v), _v[_D2]);
	 }

	 template<VecDim _D0, VecDim _D1, VecDim _D2, VecDim _D3, typename _VecT>
	 Vec4<typename _VecT::valueType> get(const _VecT & _v)
	 {
		  static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions && _D2 < _VecT::Dimensions && _D3 < _VecT::Dimensions,
				"Not enough vector dimensions to get the one(s) demanded");

		  return Vec4<typename _VecT::valueType>(get<_D0, _D1, _D2>(_v), _v[_D3]);
	 }

}} // ns

#endif // FHL_SWIZZLE_H
