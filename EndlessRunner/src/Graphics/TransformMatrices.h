#ifndef FHL_TRANSFORMMATRICES_H
#define FHL_TRANSFORMMATRICES_H

#include "../Maths/Mat4.h"

namespace fhl
{
	 struct TransformMatrices
	 {
		  bool operator==(const TransformMatrices & _other) const
		  {
				return transform == _other.transform && mvp == _other.mvp;
		  }

		  bool operator!=(const TransformMatrices & _other) const
		  {
				return !(*this == _other);
		  }

		  Mat4 transform, mvp;
	 };
}

#endif