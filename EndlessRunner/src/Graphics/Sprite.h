#ifndef FHL_SPRITE_H
#define FHL_SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ResMgr.h"
#include "Texture.h"
#include "Shader.h"
#include "Color.h"
#include "Configurator.h"
#include "Transformable.h"
#include "TexturedSizeable.h"
#include "Renderable.h"
#include "Litable.h"
#include "../Utility/OrientedRect.h"

namespace fhl { class OrientedRect; }

namespace fhl
{

	 class Sprite
		  : public Transformable,
			 public TexturedSizeable,
			 public Renderable,
			 public Litable
	 {
	 public:
		  Sprite();
		  explicit Sprite(Texture& _tex);

	 public:
		  const Texture* getTexture() const { return m_ptexture; }

		  void setShader(Shader& _shader = fhl::ResMgr::getShader(SHADER_NAME)) override;
		  void setTexture(Texture& _tex, bool _changeSize = true);
		  void setTextureRect(fhl::Rect _rect, bool _changeSize = false);
		  void setColor(const Color _color) { m_color = _color; }
		  void setLight(const Light& _light) override;
		  void render(const RenderConf & _conf) const override;
		  fhl::Rect getAABB() const;
		  fhl::OrientedRect getOBB() const;

	 private:
		  void setUp();

	 private:
		  Color m_color;
		  bool m_usingOriginalShader;

		  static bool LIGHT_SHADER_LOADED;

		  constexpr static const char* SHADER_NAME = "spriteShader";
		  constexpr static const char* LIGHT_SHADER_NAME = "spriteLightShader";
	 };

} // ns

#endif // FHL_SPRITE_H