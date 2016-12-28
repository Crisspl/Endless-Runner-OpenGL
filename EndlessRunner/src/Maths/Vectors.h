#ifndef FHL_VECTORS_H
#define FHL_VECTORS_H

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace fhl
{
		  namespace vec
		  {
				enum class Dim : size_t
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
				return{ _v[static_cast<size_t>(_D0)], _v[static_cast<size_t>(_D1)] };
		  }

		  template<vec::Dim _D0, vec::Dim _D1, vec::Dim _D2, typename _VecT>
		  Vec3<typename _VecT::valueType> get(const _VecT & _v)
		  {
				return Vec3<typename _VecT::valueType>(get<_D0, _D1>(_v), _v[static_cast<size_t>(_D2)]);
		  }

		  template<vec::Dim _D0, vec::Dim _D1, vec::Dim _D2, vec::Dim _D3, typename _VecT>
		  Vec4<typename _VecT::valueType> get(const _VecT & _v) 
		  { 
				return Vec4<typename _VecT::valueType>(get<_D0, _D1, _D2>(_v), _v[static_cast<size_t>(_D3)]);
		  }
}

#endif // FHL_VECTORS_H