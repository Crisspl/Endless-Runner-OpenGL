#ifndef FHL_RENDERMATRICES_H
#define FHL_RENDERMATRICES_H

#include "../Maths/Mat4.h"

namespace fhl
{
	 struct RenderMatrices
	 {
		  bool operator==(const RenderMatrices & _other) const
		  {
				return transform == _other.transform && mvp == _other.mvp;
		  }

		  bool operator!=(const RenderMatrices & _other) const
		  {
				return !(*this == _other);
		  }

		  Mat4 transform, mvp;
	 };
}

#endif // FHL_RENDERMATRICES_H