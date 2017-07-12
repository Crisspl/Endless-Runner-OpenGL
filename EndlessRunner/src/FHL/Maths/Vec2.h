#ifndef FHL_VEC2
#define FHL_VEC2

#include <FHL/Maths/VecBase.h>

namespace fhl
{

	template<typename _T>
	class Vec2 : public internal::VecBase<2, _T>
	{
	public:
		using valueType = _T;
		enum { Dimensions = 2 };

		constexpr explicit Vec2(_T _value = _T(0)) : internal::VecBase<2, _T>(_value) {}
		constexpr Vec2(_T _x, _T _y) : internal::VecBase<2, _T>(_x, _y) {}
		template<typename _U>
		Vec2(const Vec2<_U> & _other) : internal::VecBase<2, _T>(static_cast<const internal::VecBase<2, _T> &>(_other)) {}
		Vec2(const internal::VecBase<2, _T> & _other) : internal::VecBase<2, _T>(_other) {}

		template<typename _U>
		Vec2<_T> & operator=(const Vec2<_U> & _other) { internal::VecBase<2, _T>::operator=(_other); return *this; }

		static constexpr Vec2<_T> up() { return{ 0, 1 }; }
		static constexpr Vec2<_T> down() { return{ 0, -1 }; }
		static constexpr Vec2<_T> right() { return{ 1, 0 }; }
		static constexpr Vec2<_T> left() { return{ -1, 0 }; }
		static constexpr Vec2<_T> zero() { return{ 0, 0 }; }
		static constexpr Vec2<_T> one() { return{ 1, 1 }; }

		_T & x() { return (*this)[0]; }
		constexpr _T x() const { return (*this)[0]; }

		_T & y() { return (*this)[1]; }
		constexpr _T y() const { return (*this)[1]; }

		_FHL_VECTOR_OPERATORS_IMPLEMENTATION(_T, Vec2)
	};

	using Vec2f = Vec2<float>;
	using Vec2lf = Vec2<double>;
	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned>;

}

#endif
