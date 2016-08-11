#include "Maths_funcs.h"

namespace fhl
{

double PI = 3.141592653589793238462643383279;

double toRadians(double _deg)
{
	return _deg * PI / 180.;
}

double toDegrees(double _rad)
{
	return _rad * 180. / PI;
}

}