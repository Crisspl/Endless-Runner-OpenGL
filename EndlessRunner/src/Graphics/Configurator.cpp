#include "Configurator.h"

#include "../Utility/Debug.h"
#include "../Maths/Maths_funcs.h"

namespace fhl
{
Mat4 Configurator::ortView;
Mat4 Configurator::ortProjection;
Mat4 Configurator::perspView;
Mat4 Configurator::perspProjection;
Buffer* Configurator::rectShapeEbo;

bool Configurator::m_initialized(false);
GLuint Configurator::m_rectShapeIndices[6] =
         {
             0, 1, 3,
             1, 2, 3
         };
Vec2f Configurator::m_vpSize;
Configurator::DisplayMode Configurator::m_displMode = Configurator::Perspective;
Mat4* Configurator::m_view;
Mat4* Configurator::m_projection;

void Configurator::init(GLuint _width, GLuint _height)
{
   if(m_initialized)
      return;

   glewExperimental = GL_TRUE;

   GLenum glewError = glewInit();

   if (glewError != GLEW_OK)
	   fhl::DebugLog << "GLEW init error: " << glewGetErrorString(glewError) << '\n';

   glViewport(0, 0, _width, _height);

   Vec2f v((float)_width, (float)_height);

   m_vpSize = Vec2f(static_cast<float>(_width),
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

Vec2f Configurator::viewPortSize()
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
      ortProjection = Mat4::ortho(0.0f, m_vpSize.x, m_vpSize.y, 0.0f, -1.0f, 1.0f);
      perspProjection = Mat4::perspective(-45.f, -m_vpSize.x / m_vpSize.y, 0.1f, 10000.f);
   }
   else
   {
      ortProjection = Mat4::ortho(0.f, m_vpSize.x, 0.f, m_vpSize.y, -1.f, 1.f);
      perspProjection = Mat4::perspective(45.f, m_vpSize.x / m_vpSize.y, 0.1f, 10000.f);
   }
}

void Configurator::setPerspViewDistance(float _eyeZ)
{
   Vec2f halfVp = m_vpSize / 2.f;
   perspView = Mat4::lookAt(Vec3f(halfVp.x, halfVp.y, _eyeZ), Vec3f(halfVp.x, halfVp.y, 0), Vec3f(0, 1, 0));
}

Vec2f Configurator::getMousePosition()
{
   Vec2i mousePos;
   SDL_GetMouseState(&mousePos.x, &mousePos.y);
   return Vec2f(mousePos.x, mousePos.y);
}

} // ns
