#include "Maths_funcs.h"
#include "Constants.h"

namespace fhl
{

double toRadians(double _deg)
{
	return _deg * Constants::Pi() / 180.;
}

double toDegrees(double _rad)
{
	return _rad * 180. / Constants::Pi();
}

}