#include "Sprite.h"

#include <iostream>
#include <algorithm>

namespace gr
{

bool Sprite::LIGHT_SHADER_LOADED = false;

Sprite::Sprite()
   : WithShader(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     Litable(*m_shader),
     m_ptexture(nullptr),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   initTexCoordsArray();
   setUp();
}

Sprite::Sprite(Texture& _tex)
   : Sizeable(_tex.getSize()),
     WithShader(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     Litable(*m_shader),
     m_ptexture(&_tex),
     m_color(Color::White),
     m_usingOriginalShader(true)
{
   initTexCoordsArray();
   setUp();
}

Sprite::~Sprite()
{
/*
   glDeleteBuffers(1, &m_texCoordsBuffer);
   glDeleteBuffers(1, &m_posBuffer);
   glDeleteVertexArrays(1, &m_vao);
*/
}

void Sprite::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == ut::ResMgr::getShader(SHADER_NAME) || _shader == ut::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void Sprite::setTexture(Texture& _tex)
{
   setSize(_tex.getSize());
   m_ptexture = &_tex;
}

void Sprite::setTextureRect(ut::Rect _rect, bool _changeSize)
{
   glm::vec2 texSize = glm::vec2(m_ptexture->getSize().x, m_ptexture->getSize().y);

   if(_changeSize)
      setSize(_rect.getSize());

   for(short i = 0; i < 4; i++)
      m_texCoordsArray[i] = _rect[i] / texSize;

   uploadTexCoordsArray();
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

   glBindVertexArray(m_vao);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

   glBindTexture(GL_TEXTURE_2D, 0);
   glUseProgram(0);
}

ut::Rect Sprite::getRect() const
{
   glm::vec2 botLeft = m_position;
   botLeft -= m_transform.origin;

   return ut::Rect(botLeft, m_size);
}

void Sprite::initTexCoordsArray()
{
   m_texCoordsArray[0] = glm::vec2(0.f, 0.f);
   m_texCoordsArray[1] = glm::vec2(1.f, 0.f);
   m_texCoordsArray[2] = glm::vec2(1.f, 1.f);
   m_texCoordsArray[3] = glm::vec2(0.f, 1.f);
}

void Sprite::uploadTexCoordsArray()
{
   glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsBuffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_texCoordsArray), m_texCoordsArray);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::setUp()
{
   if(!LIGHT_SHADER_LOADED)
   {
      ut::ResMgr::loadShader(LIGHT_VSHADER_PATH, LIGHT_FSHADER_PATH, LIGHT_SHADER_NAME);
      LIGHT_SHADER_LOADED = true;
   }

   glGenVertexArrays(1, &m_vao);
   glGenBuffers(1, &m_texCoordsBuffer);

   glBindVertexArray(m_vao);

   glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(m_texCoordsArray), m_texCoordsArray, GL_DYNAMIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Configurator::rectShapeEbo);

   glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);

   glVertexAttribPointer((GLuint)AttLoc::Position, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
   glEnableVertexAttribArray((GLuint)AttLoc::Position);

   glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsBuffer);

   glVertexAttribPointer((GLuint)AttLoc::TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
   glEnableVertexAttribArray((GLuint)AttLoc::TexCoords);

   glBindVertexArray(0);
}

} // ns
