#pragma once

#include "Utility/ResMgr.h"
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
   void drawToTex(gr::Drawable& _obj);
   void drawToScreen();

private:
   gr::Shader& m_shader;
   gr::RenderTexture m_renderTex;
   gr::Sprite m_screen;
};
