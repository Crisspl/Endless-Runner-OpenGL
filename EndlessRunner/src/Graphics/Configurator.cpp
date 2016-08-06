#include "Configurator.h"

namespace fhl
{
glm::mat4 Configurator::ortView;
glm::mat4 Configurator::ortProjection;
glm::mat4 Configurator::perspView;
glm::mat4 Configurator::perspProjection;
Buffer* Configurator::rectShapeEbo;

bool Configurator::m_initialized(false);
GLuint Configurator::m_rectShapeIndices[6] =
         {
             0, 1, 3,
             1, 2, 3
         };
glm::vec2 Configurator::m_vpSize;
Configurator::DisplayMode Configurator::m_displMode = Configurator::Perspective;
glm::mat4* Configurator::m_view;
glm::mat4* Configurator::m_projection;

void Configurator::init(GLuint _width, GLuint _height)
{
   if(m_initialized)
      return;

   glewExperimental = GL_TRUE;

   GLenum glewError = glewInit();

   if (glewError != GLEW_OK)
	   std::cerr << "GLEW init error: " << glewGetErrorString(glewError) << '\n';

   glViewport(0, 0, _width, _height);

   m_vpSize = glm::vec2(static_cast<float>(_width),
						static_cast<float>(_height));

   rectShapeEbo = new Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
   rectShapeEbo->bind();
   rectShapeEbo->setData(6 * sizeof(GLuint), m_rectShapeIndices);
   rectShapeEbo->unbind();

   setFlipYAxis(1);
   setDisplayMode(m_displMode);
   setPerspViewDistance(726.f);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   m_initialized = true;
}

glm::vec2 Configurator::viewPortSize()
{
   return m_vpSize;
}

void Configurator::setDisplayMode(Configurator::DisplayMode _mode)
{
   if(_mode == Ortho)
   {
      m_view = &ortView;
      m_projection = &ortProjection;
   }
   else
   {
      m_view = &perspView;
      m_projection = &perspProjection;
   }
}

void Configurator::setFlipYAxis(bool _flip)
{
   if(_flip)
   {
      ortProjection = glm::ortho(0.0f, m_vpSize.x, m_vpSize.y, 0.0f, -1.0f, 1.0f);
      perspProjection = glm::perspective(glm::radians(-45.f), -m_vpSize.x / m_vpSize.y, 0.1f, 10000.f);
   }
   else
   {
      ortProjection = glm::ortho(0.f, m_vpSize.x, 0.f, m_vpSize.y, -1.f, 1.f);
      perspProjection = glm::perspective(glm::radians(45.f), m_vpSize.x / m_vpSize.y, 0.1f, 10000.f);
   }
}

void Configurator::setPerspViewDistance(float _eyeZ)
{
   glm::vec2 halfVp = m_vpSize / 2.f;
   perspView = glm::lookAt(glm::vec3(halfVp.x, halfVp.y, _eyeZ), glm::vec3(halfVp.x, halfVp.y, 0), glm::vec3(0, 1, 0));
}

glm::vec2 Configurator::getMousePosition()
{
   glm::tvec2<int> mousePos;
   SDL_GetMouseState(&mousePos.x, &mousePos.y);
   return glm::vec2(mousePos.x, mousePos.y);
}

} // ns
