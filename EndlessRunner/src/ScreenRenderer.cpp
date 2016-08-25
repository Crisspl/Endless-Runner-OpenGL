#include "ScreenRenderer.h"
#include "Graphics/DrawFuncs.h"

ScreenRenderer::ScreenRenderer()
      : m_shader(fhl::ResMgr::loadShader("Graphics/Shaders/screen_vs.glsl", "Graphics/Shaders/screen_fs.glsl", "screenShader")),
        m_renderTex(fhl::ResMgr::loadTexture(glm::tvec2<GLint>(800, 600), "screenTex")),
        m_screen(m_renderTex.getTexture())
{
   m_renderTex.create();
   m_screen.setShader(m_shader);
   m_screen.setSize({2, 2});
}

void ScreenRenderer::clearColor(glm::vec4 _color)
{
   m_renderTex.clearColor(_color);
}

void ScreenRenderer::drawToTex(fhl::Drawable& _obj)
{
   m_renderTex.drawToTex(_obj);
}

void ScreenRenderer::drawToScreen()
{
	fhl::draw(m_screen);
}
