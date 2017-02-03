#ifndef FHL_CONFIGURATOR_H
#define FHL_CONFIGURATOR_H

#include <GL/glew.h>

#include <SDL.h>

#include <iostream>

#include "Buffer.h"
#include "../Maths/vectors.h"
#include "../Maths/Mat4.h"

namespace fhl
{

	 class Configurator
	 {
		  Configurator() = delete;

	 public:
		  enum DisplayMode
		  {
				Ortho,
				Perspective
		  };

	 public:
		  static void init(GLuint _width, GLuint _height);

		  static Vec2f viewPortSize();

		  static const Mat4& view() { return *m_view; }

		  static const Mat4& projection() { return *m_projection; }

		  static void setDisplayMode(DisplayMode _mode);

		  static void setFlipYAxis(bool _flip);

		  static void setPerspViewDistance(float _eyeZ);

		  static Vec2f getMousePosition();

	 public:
		  static Mat4 ortView, ortProjection, perspView, perspProjection;
		  static Buffer* rectShapeEbo;

	 private:
		  static bool m_initialized;
		  static GLuint m_rectShapeIndices[6];
		  static Vec2f m_vpSize;
		  static DisplayMode m_displMode;
		  static Mat4* m_view;
		  static Mat4* m_projection;
	 };

} // ns

#endif // FHL_CONFIGURATOR_H
