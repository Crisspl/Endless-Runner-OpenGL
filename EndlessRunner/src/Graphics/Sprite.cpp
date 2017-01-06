#include "Sprite.h"

#include <iostream>
#include <algorithm>

namespace fhl
{

	 Sprite::Sprite()
		  : TexturedSizeable(nullptr),
		  UsingShader(&ResMgr::getLoadShader(SHADER_NAME, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::getLoadShader(LIGHT_SHADER_NAME, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White),
		  m_usingOriginalShader(true)
	 {
		  setUp();
	 }

	 Sprite::Sprite(Texture& _tex)
		  : TexturedSizeable(&_tex, _tex.getSize()),
		  UsingShader(&ResMgr::getLoadShader(SHADER_NAME, shaderSrcs::sprite_Vertex, shaderSrcs::sprite_Fragment, Shader::FromString),
						  &ResMgr::getLoadShader(LIGHT_SHADER_NAME, shaderSrcs::sprite_LightVertex, shaderSrcs::sprite_LightFragment, Shader::FromString)),
		  m_color(Color::White),
		  m_usingOriginalShader(true)
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
		  Shader & shader = *m_shader;
		  shader.use();

		  glActiveTexture(GL_TEXTURE0);
		  shader.setInt("texSampler", 0);
		  shader.setColor("color", m_color);

		  const Transform* transform = (_conf == RenderConf::Default) ? &m_transform : &_conf.transform;

		  if (m_ptexture)
				glBindTexture(GL_TEXTURE_2D, m_ptexture->getId());

		  if (m_usingOriginalShader)
		  {
				shader.setMat4("translation", transform->translation)
					 .setMat4("rotation", transform->rotation)
					 .setMat4("scale", transform->scale)
					 .setMat4("view", Configurator::view())
					 .setMat4("projection", Configurator::projection())
					 .setLights("light", getLights().cbegin(), getLights().cend());
		  }

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