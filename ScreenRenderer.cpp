#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer()
      : m_shader(ut::ResMgr::getShader("screenShader")),
        m_renderTex(ut::ResMgr::getTexture("screenTex")),
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

void ScreenRenderer::drawToTex(gr::Drawable& _obj)
{
   m_renderTex.drawToTex(_obj);
}

void ScreenRenderer::drawToScreen()
{
   m_screen.draw();
}
