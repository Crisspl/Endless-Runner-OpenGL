#ifndef FHL_USINGSHADER_H
#define FHL_USINGSHADER_H

#include "Shader.h"

namespace fhl
{
	 class UsingShader
	 {
	 public:
		  struct DefaultShader_t {};
		  struct LightShader_t {};

		  UsingShader(Shader * _default, Shader * _light) : m_defaultShader(_default), m_lightShader(_light), m_shader(_default) { }

		  void setShader(DefaultShader_t) { m_shader = m_defaultShader; }
		  void setShader(LightShader_t) { m_shader = m_lightShader; }
		  void setShader(Shader & _shader) { m_shader = &_shader; }

	 public:
		  static DefaultShader_t Default;
		  static LightShader_t Light;

	 private:
		  Shader * m_defaultShader, * m_lightShader;

	 protected:
		  Shader * m_shader;
	 };
}

#endif // FHL_USINGSHADER_H
