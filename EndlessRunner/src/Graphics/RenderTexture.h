#ifndef FHL_RENDERTEXTURE_H
#define FHL_RENDERTEXTURE_H

#include <GL/glew.h>
#include <iostream>

#include "Texture.h"
#include "Drawable.h"

namespace fhl
{

class RenderTexture // TODO
{
public:
   explicit RenderTexture(Texture& _tex);

   bool create();
   void clearColor(Vec4f _color);
   void drawToTex(Drawable& _obj);
   Texture& getTexture() { return m_refTex; }

private:
   GLuint m_fbo, m_rbo;
   Texture& m_refTex;
};

} // ns

#endif // FHL_RENDERTEXTURE_H
