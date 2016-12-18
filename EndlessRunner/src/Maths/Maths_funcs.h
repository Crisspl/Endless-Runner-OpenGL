#ifndef MATHS_FUNCS
#define MATHS_FUNCS

#include <cmath>

namespace fhl
{
	double toRadians(double _deg);
	double toDegrees(double _rad);

	template <typename _T>
	_T clamp(_T _n, _T _lo, _T _hi)
	{
		return std::max(_lo, std::min(_n, _hi));
	}
}

#endif // MATHS_FUNCS
