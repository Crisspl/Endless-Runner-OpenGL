#ifndef FHL_VIEW_H
#define FHL_VIEW_H

#include "../Maths/Mat4.h"

namespace fhl
{

	struct View
	{
		Mat4 matrix;
		Vec3f cameraPos;
	};

}

#endif // FHL_VIEW_H
