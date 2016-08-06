#include "RenderTexture.h"

#include "../Utility/Debug.h"

namespace fhl
{

RenderTexture::RenderTexture(Texture& _tex)
      : m_refTex(_tex)
{
}

bool RenderTexture::create()
{
   glGenFramebuffers(1, &m_fbo);
   glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_refTex.getId(), 0);

   glGenRenderbuffers(1, &m_rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_refTex.getSize().x, m_refTex.getSize().y);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
   {
      fhl::DebugLog << "Framebuffer is not complete! <fhl::RenderTexture>" << '\n';
      return false;
   }
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   return true;
}

void RenderTexture::clearColor(glm::vec4 _color)
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
   glClearColor(_color.x, _color.y, _color.z, _color.w);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::drawToTex(Drawable& _obj)
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
   _obj.draw();
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // ns
