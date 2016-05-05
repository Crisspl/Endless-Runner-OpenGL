#include "ColoredRect.h"

namespace gr
{

bool ColoredRect::LIGHT_SHADER_LOADED = false;

ColoredRect::ColoredRect(glm::vec2 _size)
   : Sizeable(_size),
     WithShader(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     Litable(*m_shader),
     m_color(Color::Transparent),
     m_vao(new Vao()),
     m_usingOriginalShader(true)
{
   setUp();
}

void ColoredRect::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == ut::ResMgr::getShader(SHADER_NAME) || _shader == ut::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void ColoredRect::setLight(const Light& _light)
{
   m_shader = &ut::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   m_shader->setLight("light", _light);
}

void ColoredRect::draw() const
{
   m_shader->use();

   glm::vec4 normColor = m_color.normalized();

   m_shader->setMat4("translation", m_transform.translation)
           .setMat4("rotation", m_transform.rotation)
           .setMat4("scale", m_transform.scale)
           .setMat4("projection", Configurator::projection())
           .setMat4("view", Configurator::view())
           .setVec4f("vertColor", normColor);

   m_vao->bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   m_vao->unbind();

   Shader::unUse();
}

void ColoredRect::setUp()
{
   if(!LIGHT_SHADER_LOADED)
   {
      ut::ResMgr::loadShader(LIGHT_VSHADER_PATH, LIGHT_FSHADER_PATH, LIGHT_SHADER_NAME);
      LIGHT_SHADER_LOADED = true;
   }

   m_vao->bind();

   Configurator::rectShapeEbo->bind();

   m_posBuffer->bind();

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   m_vao->unbind();
}

}
