#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include "Graphics/ResMgr.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/Shader.h"
#include "Graphics/Drawable.h"
#include "Graphics/Configurator.h"
#include "Graphics/Sprite.h"

class ScreenRenderer
{
public:
   ScreenRenderer();

public:
   void clearColor(glm::vec4 _color);
   void drawToTex(fhl::Drawable& _obj);
   void drawToScreen();

private:
   fhl::Shader& m_shader;
   fhl::RenderTexture m_renderTex;
   fhl::Sprite m_screen;
};

#endif // SCREENRENDERER_H
