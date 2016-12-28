#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include "Graphics/ResMgr.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/Shader.h"
#include "Graphics/Renderable.h"
#include "Graphics/Configurator.h"
#include "Graphics/Sprite.h"

class ScreenRenderer
{
public:
   ScreenRenderer();

public:
   void clearColor(fhl::Vec4f _color);
   void renderToTex(fhl::Renderable & _obj);
   void renderToScreen();

private:
   fhl::Shader& m_shader;
   fhl::RenderTexture m_renderTex;
   fhl::Sprite m_screen;
};

#endif // SCREENRENDERER_H
