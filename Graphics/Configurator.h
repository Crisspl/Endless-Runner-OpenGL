#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL.h>

#include <iostream>

#include "Buffer.h"

namespace gr
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
   static void init();

   static glm::vec2 viewPortSize();

   static const glm::mat4& view() { return *m_view; }

   static const glm::mat4& projection() { return *m_projection; }

   static void setDisplayMode(DisplayMode _mode);

   static void setFlipYAxis(bool _flip);

   static void setPerspViewDistance(float _eyeZ);

   static glm::vec2 getMousePosition();

public:
   static glm::mat4 ortView, ortProjection, perspView, perspProjection;
   static Buffer* rectShapeEbo;

private:
   static bool m_initialized;
   static GLuint m_rectShapeIndices[6];
   static glm::vec2 m_vpSize;
   static DisplayMode m_displMode;
   static glm::mat4* m_view;
   static glm::mat4* m_projection;
};

} // ns
