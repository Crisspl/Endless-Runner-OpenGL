#ifndef FHL_COLOREDRECT_H
#define FHL_COLOREDRECT_H

#include <GL/glew.h>

#include "Renderable.h"
#include "Vao.h"
#include "Transformable.h"
#include "Sizeable.h"
#include "Shader.h"
#include "Vertex.h"
#include "ResMgr.h"
#include "Litable.h"
#include "UsingShader.h"

namespace fhl
{

	 class ColoredRect
		  : public Transformable,
			public Sizeable,
			public UsingShader,
			public Renderable,
			public Litable
	 {
	 public:
		  explicit ColoredRect(Vec2f _size);

		  Color getColor() const { return m_color; }

		  ColoredRect & setColor(Color _color) { m_color = _color; return *this; }

		  void render(const RenderConf & _conf) const override;

	 private:
		  void setUp();

	 private:
		  Color m_color;
		  bool m_usingOriginalShader;

		  constexpr static const char* SHADER_NAME = "rectShader";
		  constexpr static const char* LIGHT_SHADER_NAME = "rectLightShader";
	 };

}

#endif // FHL_COLOREDRECT_H