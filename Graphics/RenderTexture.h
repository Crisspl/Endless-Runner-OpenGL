#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

#include "Texture.h"
#include "Drawable.h"

namespace gr
{

class RenderTexture // TODO
{
public:
   explicit RenderTexture(Texture& _tex);

   bool create();
   void clearColor(glm::vec4 _color);
   void drawToTex(Drawable& _obj);
   Texture& getTexture() { return m_refTex; }

private:
   GLuint m_fbo, m_rbo;
   Texture& m_refTex;
};

} // ns
