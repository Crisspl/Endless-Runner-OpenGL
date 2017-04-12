#ifndef FHL_USINGGL_H
#define FHL_USINGGL_H

#include "Configurator.h"

namespace fhl
{

	class UsingGl
	{
	public:
		UsingGl()
		{
			Configurator::initGLEW();
		}
		UsingGl(UsingGl &&) = default;
		UsingGl & operator=(UsingGl &&) = default;

		virtual ~UsingGl() = default;
	};

}

#endif // FHL_USINGGL_H
