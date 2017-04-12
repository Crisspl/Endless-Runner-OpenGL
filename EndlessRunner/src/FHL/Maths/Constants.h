#ifndef FHL_CONSTANTS_H
#define FHL_COSNTANTS_H

namespace fhl
{

	template<typename _T>
	struct Constants
	{
		Constants() = delete;

		constexpr static double Pi() { return _T(3.141592653589793238); }

		constexpr static double e() { return _T(2.718281828459045235); }

		constexpr static double sqrt2() { return _T(1.414213562373095048); }

		constexpr static double sqrt3() { return _T(1.732050807568877293); }
	};

}

#endif // FHL_CONSTANTS_H
