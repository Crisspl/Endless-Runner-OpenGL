#ifndef FHL_WITHSHADER_H
#define FHL_WITHSHADER_H

#include "Shader.h"

namespace fhl
{

	 class WithShader
	 {
	 public:
		 WithShader(Shader& _shader);
		 virtual ~WithShader() { }

		 virtual const Shader& getShader() const;
		 virtual void setShader(Shader& _shader);

	 protected:
		 Shader* m_shader;
	 };

} // ns

#endif // FHL_WITHSHADER_H
