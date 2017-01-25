#include "Sprite.h"
#include "ResMgr.h"

#include <iostream>
#include <algorithm>

namespace fhl
{

	 Sprite::Sprite()
		  : TexturedSizeable(nullptr),
		  UsingShader(&ResMgr::loadShader(simpleShaderName, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::loadShader(lightShaderName, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White)
	 {
		  setUp();
	 }

	 Sprite::Sprite(Texture& _tex)
		  : TexturedSizeable(&_tex, _tex.getSize()),
		  UsingShader(&ResMgr::loadShader(simpleShaderName, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::loadShader(lightShaderName, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White)
	 {
		  setUp();
	 }

	 void Sprite::setTexture(Texture& _tex, bool _changeSize)
	 {
		  m_ptexture = &_tex;
		  if (_changeSize)
				setSize(_tex.getSize());
	 }

	 void Sprite::setTextureRect(fhl::Rect _rect, bool _changeSize)
	 {
		  if (!m_ptexture)
				return;

		  Vec2f texSize = Vec2f(m_ptexture->getSize().x, m_ptexture->getSize().y);

		  if (_changeSize)
				setSize(_rect.getSize());

		  for (short i = 0; i < 4; i++)
				m_texCoordsArray[i] = _rect[i] / texSize;

		  TexturedSizeable::uploadTexCoordsArray();
	 }

	 void Sprite::render(const RenderConf & _conf) const
	 {
		  Shader & shader = *getShader();
		  shader.use();

		  glActiveTexture(GL_TEXTURE0);
		  shader.setInt("texSampler", 0);
		  shader.setColor("color", m_color);

		  bool useCustomConf = _conf != RenderConf::Default;

		  if (m_ptexture)
				glBindTexture(GL_TEXTURE_2D, m_ptexture->getId());

		  shader.setMat4("mvp", useCustomConf ? _conf.matrices.mvp : getMVP())
				.setMat4("model", useCustomConf ? _conf.matrices.transform : getTransform())
				.setLights("light", getLights().cbegin(), getLights().cend());

		  m_vao->bind();
		  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  m_vao->unbind();

		  glBindTexture(GL_TEXTURE_2D, 0);
		  glUseProgram(0);
	 }

	 fhl::Rect Sprite::getAABB() const
	 {
		  Vec2f bl = getPosition() - getOrigin();
		  return fhl::Rect(bl, m_size);
	 }

	 fhl::OrientedRect Sprite::getOBB() const
	 {
		  fhl::OrientedRect rect(m_size, getTransformData());

		  return rect;
	 }

	 void Sprite::setUp()
	 {
		  m_vao->bind();

		  Configurator::rectShapeEbo->bind();

		  m_vao->unbind();
	 }

} // ns