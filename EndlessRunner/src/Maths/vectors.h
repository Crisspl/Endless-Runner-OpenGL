#ifndef FHL_VECTORS_H
#define FHL_VECTORS_H

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace fhl
{
		  namespace vec
		  {
				enum Dim
				{
					 X = 0,
					 Y = 1,
					 Z = 2,
					 W = 3
				};
		  }

		  template<vec::Dim _D0, vec::Dim _D1, typename _VecT>
		  Vec2<typename _VecT::valueType> get(const _VecT & _v) 
		  { 
				static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions,
									 "Not enough vector dimensions to get the one demanded");

				return{ _v[_D0], _v[_D1] };
		  }

		  template<vec::Dim _D0, vec::Dim _D1, vec::Dim _D2, typename _VecT>
		  Vec3<typename _VecT::valueType> get(const _VecT & _v) 
		  {
				static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions && _D2 < _VecT::Dimensions,
									 "Not enough vector dimensions to get the one demanded");

				return Vec3<typename _VecT::valueType>(get<_D0, _D1>(_v), _v[_D2]);
		  }

		  template<vec::Dim _D0, vec::Dim _D1, vec::Dim _D2, vec::Dim _D3, typename _VecT>
		  Vec4<typename _VecT::valueType> get(const _VecT & _v) 
		  { 
				static_assert(_D0 < _VecT::Dimensions && _D1 < _VecT::Dimensions && _D2 < _VecT::Dimensions && _D3 < _VecT::Dimensions,
									 "Not enough vector dimensions to get the one demanded");

				return Vec4<typename _VecT::valueType>(get<_D0, _D1, _D2>(_v), _v[_D3]);
		  }
}

#endif // FHL_VECTORS_H
