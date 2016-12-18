#include "ScreenRenderer.h"
#include "Graphics/DrawFuncs.h"

ScreenRenderer::ScreenRenderer()
      : m_shader(fhl::ResMgr::loadShader("Resources/ShaderSrcs/screen_vs.glsl", "Resources/ShaderSrcs/screen_fs.glsl", "screenShader", fhl::Shader::FromFile)),
        m_renderTex(fhl::ResMgr::loadTexture(fhl::Vec2i(800, 600), "screenTex")),
        m_screen(m_renderTex.getTexture())
{
   m_renderTex.create();
   m_screen.setShader(m_shader);
   m_screen.setSize({2, 2});
   m_screen.setTextureRect(fhl::Rect(m_renderTex.getTexture().getSize()));
}

void ScreenRenderer::clearColor(fhl::Vec4f _color)
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
