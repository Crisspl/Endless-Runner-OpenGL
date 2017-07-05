#ifndef FHL_SWIZZLE_H
#define FHL_SWIZZLE_H

#include <type_traits>

#include <FHL/Maths/vectors.h>

namespace fhl { namespace swizzle
{

	namespace impl
	{
		template<std::size_t DimsCount, typename _ValT>
		struct VectorTypeForSize {};

		template<typename _ValT>
		struct VectorTypeForSize<2, _ValT> { using Type = Vec2<_ValT>; };

		template<typename _ValT>
		struct VectorTypeForSize<3, _ValT> { using Type = Vec3<_ValT>; };

		template<typename _ValT>
		struct VectorTypeForSize<4, _ValT> { using Type = Vec4<_ValT>; };


		template<bool...>
		struct allTrue : std::false_type {};

		template<bool FirstCond, bool... Conds>
		struct allTrue<FirstCond, Conds...> : std::integral_constant<bool, FirstCond && allTrue<Conds...>::value> {};

		template<bool Cond>
		struct allTrue<Cond> : std::integral_constant<bool, Cond> {};

		template<>
		struct allTrue<> : std::true_type {};
	}

	enum VecDim
	{
		X = 0, x = 0, R = 0, r = 0,
		Y = 1, y = 1, G = 1, g = 1,
		Z = 2, z = 2, B = 2, b = 2,
		W = 3, w = 3, A = 3, a = 3
	};

	template<VecDim ...Dims, typename VecT>
	constexpr typename impl::VectorTypeForSize<sizeof...(Dims), typename VecT::valueType>::Type
	get(const VecT & _v)
	{
		static_assert(impl::allTrue<(Dims < VecT::Dimensions)...>::value, "Not enough vector dimensions to get the one(s) demanded");
		static_assert(sizeof...(Dims) <= 4, "Cannot create a Vector of more than 4 dimensions");

		return{ _v[Dims]... };
	}

}}

#endif // FHL_SWIZZLE_H
