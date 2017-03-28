#include "Sprite.h"
#include "ResMgr.h"

#include <iostream>
#include <algorithm>

namespace fhl
{

	 Sprite::Sprite() : 
		  TexturedSizeable(nullptr),
		  UsingShader(&ResMgr::loadShader(simpleShaderName, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::loadShader(lightShaderName, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White)
	 {
		  setUp();
	 }

	 Sprite::Sprite(Texture & _tex) :
		  TexturedSizeable(&_tex, _tex.getSize()),
		  UsingShader(&ResMgr::loadShader(simpleShaderName, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::loadShader(lightShaderName, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White)
	 {
		  setUp();
	 }

	 void Sprite::render(const RenderConf & _conf) const
	 {
		  if (!getShader())
				return;

		  Shader & shader = *getShader();
		  shader.use();

		  glActiveTexture(GL_TEXTURE0);
		  shader.setInt("texSampler", 0);
		  shader.setColor("color", m_color);

		  bool useCustomConf = _conf != RenderConf::Default;

		  if (useCustomConf && _conf.texture)
				glBindTexture(GL_TEXTURE_2D, _conf.texture->getId());
		  else if (getTexture())
				glBindTexture(GL_TEXTURE_2D, getTexture()->getId());

		  const auto & lights = useCustomConf ? _conf.lights : getLights();

		  shader.setMat4("mvp", useCustomConf ? _conf.matrices.mvp : getMVP())
				.setMat4("model", useCustomConf ? _conf.matrices.transform : getTransform())
				.setLights("light", lights.cbegin(), lights.cend());

		  getVao().bind();
		  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  getVao().unbind();

		  glBindTexture(GL_TEXTURE_2D, 0);
		  glUseProgram(0);
	 }

	 fhl::Rect Sprite::getAABB() const
	 {
		  Vec2f bl = getPosition() - getOrigin();
		  return fhl::Rect(bl, getSize());
	 }

	 fhl::OrientedRect Sprite::getOBB() const
	 {
		  fhl::OrientedRect rect(getSize(), getTransformData());

		  return rect;
	 }

	 void Sprite::setUp()
	 {
		  getVao().bind();

		  Configurator::getRectShapeEbo().bind();

		  getVao().unbind();
	 }

} // ns