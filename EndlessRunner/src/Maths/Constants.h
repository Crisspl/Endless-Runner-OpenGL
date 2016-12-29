#ifndef FHL_CONSTANTS_H
#define FHL_COSNTANTS_H

namespace fhl
{

	 struct Constants
	 {
		  Constants() = delete;

		  constexpr static double Pi()		{ return 3.141592653589793; }

		  constexpr static double e()		{ return 2.718281828459045; }

		  constexpr static double sqrt2() { return 1.414213562373095; }

		  constexpr static double sqrt3() { return 1.732050807568877; }
	 };

}

#endif // FHL_CONSTANTS_H
