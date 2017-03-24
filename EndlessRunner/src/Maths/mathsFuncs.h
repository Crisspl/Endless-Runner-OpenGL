#ifndef FHL_MATHS_FUNCS
#define FHL_MATHS_FUNCS

#include <algorithm>
#include "Constants.h"

namespace fhl
{
	 constexpr double toRadians(double _deg) { return _deg * Constants::Pi() / 180.; }
	 constexpr double toDegrees(double _rad) { return _rad * 180. / Constants::Pi(); }

	 template <typename _T>
	 constexpr _T clamp(_T _n, _T _lo, _T _hi)
	 {
		  return std::max(_lo, std::min(_n, _hi));
	 }
}

#endif // FHL_MATHS_FUNCS
