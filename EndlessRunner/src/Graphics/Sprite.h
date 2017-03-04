#ifndef FHL_SPRITE_H
#define FHL_SPRITE_H

#include <GL/glew.h>

#include "Texture.h"
#include "Shader.h"
#include "Color.h"
#include "Configurator.h"
#include "Transformable.h"
#include "TexturedSizeable.h"
#include "Renderable.h"
#include "UsingShader.h"
#include "Litable.h"
#include "../Utility/OrientedRect.h"

namespace fhl
{
	 class OrientedRect;
	 class ResMgr;

	 class Sprite :
		  public Transformable,
		  public internal::TexturedSizeable,
		  public UsingShader,
		  public Renderable,
		  public Litable
	 {
		  friend class ResMgr;

	 public:
			Sprite();
			explicit Sprite(Texture & _tex);

	 public:
			void setColor(const Color _color) { m_color = _color; }
			void render(const RenderConf & _conf) const override;
			Rect getAABB() const;
			OrientedRect getOBB() const;

	 private:
			void setUp();

	 private:
			Color m_color;

			constexpr static const char * simpleShaderName = "_FHL_spriteSimpleShader";
			constexpr static const char * lightShaderName = "_FHL_spriteLightShader";
	 };

} // ns

#endif // FHL_SPRITE_H