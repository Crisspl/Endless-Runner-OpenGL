#include "Sprite.h"

#include <iostream>
#include <algorithm>

namespace fhl
{

bool Sprite::LIGHT_SHADER_LOADED = false;

Sprite::Sprite()
   : TexturedSizeable(nullptr),
     Litable(fhl::ResMgr::isShaderLoaded(SHADER_NAME) ? fhl::ResMgr::getShader(SHADER_NAME) : fhl::ResMgr::loadShader(fhl::shaderSrcs::sprite_Vertex, fhl::shaderSrcs::sprite_Fragment, SHADER_NAME, Shader::FromString)),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   setUp();
}

Sprite::Sprite(Texture& _tex)
   : TexturedSizeable(&_tex, _tex.getSize()),
     Litable(fhl::ResMgr::isShaderLoaded(SHADER_NAME) ? fhl::ResMgr::getShader(SHADER_NAME) : fhl::ResMgr::loadShader(fhl::shaderSrcs::sprite_Vertex, fhl::shaderSrcs::sprite_Fragment, SHADER_NAME, Shader::FromString)),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   setUp();
}

void Sprite::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == fhl::ResMgr::getShader(SHADER_NAME) || _shader == fhl::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void Sprite::setTexture(Texture& _tex, bool _changeSize)
{
   m_ptexture = &_tex;
   if(_changeSize)
      setSize(_tex.getSize());
}

void Sprite::setTextureRect(fhl::Rect _rect, bool _changeSize)
{
   if(!m_ptexture)
      return;

   glm::vec2 texSize = glm::vec2(m_ptexture->getSize().x, m_ptexture->getSize().y);

   if(_changeSize)
      setSize(_rect.getSize());

   for(short i = 0; i < 4; i++)
      m_texCoordsArray[i] = _rect[i] / texSize;

   TexturedSizeable::uploadTexCoordsArray();
}

void Sprite::setLight(const Light& _light)
{
   m_shader = &fhl::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   m_shader->setLight("light", _light);
}

void Sprite::draw(const DrawConf & _conf) const
{
   Shader& shader = *m_shader;
   shader.use();

   glActiveTexture(GL_TEXTURE0);
   shader.setInt("texSampler", 0);
   shader.setColor("color", m_color);

   const Transform* transform = (_conf == DrawConf::Default) ? &m_transform : &_conf.transform;

   if(m_ptexture)
      glBindTexture(GL_TEXTURE_2D, m_ptexture->getId());

   if(m_usingOriginalShader)
   {
      shader.setMat4("translation", transform->translation)
            .setMat4("rotation", transform->rotation)
            .setMat4("scale", transform->scale)
            .setMat4("view", Configurator::view())
            .setMat4("projection", Configurator::projection());
   }

   m_vao->bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   m_vao->unbind();

   glBindTexture(GL_TEXTURE_2D, 0);
   glUseProgram(0);
}

fhl::Rect Sprite::getAABB() const
{
   glm::vec2 bl = getPosition() - getOrigin();
   return fhl::Rect(bl, m_size);
}

fhl::OrientedRect Sprite::getOBB() const
{
   fhl::OrientedRect rect(m_size, getTransformData());

   return rect;
}

void Sprite::setUp()
{
   if(!LIGHT_SHADER_LOADED)
   {
      fhl::ResMgr::loadShader(fhl::shaderSrcs::sprite_LightVertex, fhl::shaderSrcs::sprite_LightFragment, LIGHT_SHADER_NAME, Shader::FromString);
      LIGHT_SHADER_LOADED = true;
   }

   m_vao->bind();
   Configurator::rectShapeEbo->bind();
   m_vao->unbind();
}

} // ns
