#ifndef FHL_RENDERTEXTURE_H
#define FHL_RENDERTEXTURE_H

#include <GL/glew.h>

#include <algorithm>
#include <functional>

#include "Texture.h"
#include "Renderable.h"

namespace fhl
{

	class RenderTexture
	{
#define GEN_GL_OBJECT_TRAITS_CLASS(Name, Create, Destroy, BindTarget, Bind) \
struct Name \
{ \
	static GLuint create() \
	{ \
		GLuint id; \
		Create(1, &id); \
		return id; \
	} \
	static void destroy(GLuint _id) \
	{ \
		Destroy(1, &_id); \
	} \
	static void bind(GLuint _id) \
	{ \
		Bind(BindTarget, _id); \
	} \
};

GEN_GL_OBJECT_TRAITS_CLASS(GlRboTraits, glGenRenderbuffers, glDeleteRenderbuffers, GL_RENDERBUFFER, glBindRenderbuffer)
GEN_GL_OBJECT_TRAITS_CLASS(GlFboTraits, glGenFramebuffers, glDeleteFramebuffers, GL_FRAMEBUFFER, glBindFramebuffer)

#undef GEN_GL_OBJECT_TRAITS_CLASS

		template<typename _Traits>
		struct GlObject
		{
			GlObject() : id(_Traits::create()) {}
			GlObject(GlObject && _other) : id(_other) { _other.id = 0; }
			GlObject & operator=(GlObject && _other) 
			{ 
				std::swap(id, _other.id);
				return *this;
			}
			virtual ~GlObject() { _Traits::destroy(id); }

			operator GLuint() const { return id; }

			void bind() const { _Traits::bind(id); }
			void unbind() const { _Traits::bind(0); }

			GLuint id;
		};

		struct GlRbo : GlObject<GlRboTraits>
		{
			void establishStorage(Vec2i _size) { glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _size.x, _size.y); }
		};
		struct GlFbo : GlObject<GlFboTraits>
		{
			void attachTexture(GLuint _texId) const { glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texId, 0); }
			void attachRbo(GLuint _rboId) const { glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rboId); }
		};

	public:
		explicit RenderTexture(Texture & _tex);
		RenderTexture(const RenderTexture &) = delete;
		RenderTexture & operator=(const RenderTexture &) = delete;

		void clearColor(Color _color) const;
		void renderToTex(Renderable & _renderable, const RenderConf & _conf = RenderConf::Default) const;
		Texture & getTexture() { return m_tex; }

	private:
		void setUp();

	private:
		GlFbo m_fbo;
		GlRbo m_rbo;
		std::reference_wrapper<Texture> m_tex;
	};

} // ns

#endif // FHL_RENDERTEXTURE_H