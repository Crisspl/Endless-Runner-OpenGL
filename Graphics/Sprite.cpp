#include "Sprite.h"

#include <iostream>
#include <algorithm>

namespace gr
{

bool Sprite::LIGHT_SHADER_LOADED = false;

Sprite::Sprite()
   : Litable(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     TexturedSizeable(nullptr),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   setUp();
}

Sprite::Sprite(Texture& _tex)
   : TexturedSizeable(&_tex, _tex.getSize()),
     Litable(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   setUp();
}

void Sprite::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == ut::ResMgr::getShader(SHADER_NAME) || _shader == ut::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void Sprite::setTexture(Texture& _tex)
{
   m_ptexture = &_tex;
   setSize(_tex.getSize());
}

void Sprite::setTextureRect(ut::Rect _rect, bool _changeSize)
{
   glm::vec2 texSize = glm::vec2(m_ptexture->getSize().x, m_ptexture->getSize().y);

   if(_changeSize)
      setSize(_rect.getSize());

   for(short i = 0; i < 4; i++)
      m_texCoordsArray[i] = _rect[i] / texSize;

   TexturedSizeable::uploadTexCoordsArray();
}

void Sprite::setLight(const Light& _light)
{
   m_shader = &ut::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   m_shader->setLight("light", _light);
}

void Sprite::draw() const
{
   Shader& shader = *m_shader;
   shader.use();

   glActiveTexture(GL_TEXTURE0);
   shader.setInt("texSampler", 0);
   shader.setColor("color", m_color);

   glBindTexture(GL_TEXTURE_2D, m_ptexture->getId());

   if(m_usingOriginalShader)
   {
      shader.setMat4("translation", m_transform.translation)
            .setMat4("rotation", m_transform.rotation)
            .setMat4("scale", m_transform.scale)
            .setMat4("view", Configurator::view())
            .setMat4("projection", Configurator::projection());
   }

   m_vao->bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   m_vao->unbind();

   glBindTexture(GL_TEXTURE_2D, 0);
   glUseProgram(0);
}

ut::Rect Sprite::getAABB() const
{
   glm::vec2 bl = getPosition() - getOrigin();
   return ut::Rect(bl, m_size);
}

ut::OrientedRect Sprite::getOBB() const
{
   ut::OrientedRect rect(m_size, getTransformData());

   return rect;
}

void Sprite::setUp()
{
   if(!LIGHT_SHADER_LOADED)
   {
      ut::ResMgr::loadShader(LIGHT_VSHADER_PATH, LIGHT_FSHADER_PATH, LIGHT_SHADER_NAME);
      LIGHT_SHADER_LOADED = true;
   }

   m_vao->bind();
   Configurator::rectShapeEbo->bind();
   m_vao->unbind();
}

} // ns
