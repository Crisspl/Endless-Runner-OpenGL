#include "RenderTexture.h"

#include "../Utility/Debug.h"
#include "Renderer.h"
#include "ResMgr.h"

namespace fhl
{
	RenderTexture::RenderTexture(Texture & _tex) :
		m_tex(_tex)
	{
		setUp();
	}

	void RenderTexture::clearColor(Color _color) const
	{
		m_fbo.bind();
		glClearColor(_color.r, _color.g, _color.b, _color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_fbo.unbind();
	}

	void RenderTexture::renderToTex(Renderable & _renderable, const RenderConf & _conf) const
	{
		m_fbo.bind();
		Renderer::render(_renderable, _conf);
		m_fbo.unbind();
	}

	void RenderTexture::setUp()
	{
		m_fbo.bind();

		m_fbo.attachTexture(m_tex.get().getId());
		m_rbo.bind();
		m_rbo.establishStorage(m_tex.get().getSize());
		m_rbo.unbind();
		m_fbo.attachRbo(m_rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			fhl::DebugLog << "Framebuffer is not complete! <fhl::RenderTexture>\n";

		m_fbo.unbind();
	}

}
