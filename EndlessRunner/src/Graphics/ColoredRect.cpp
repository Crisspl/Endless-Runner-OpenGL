#include "ColoredRect.h"

namespace fhl
{

bool ColoredRect::LIGHT_SHADER_LOADED = false;

ColoredRect::ColoredRect(glm::vec2 _size)
   : Sizeable(_size),
     Litable(fhl::ResMgr::isShaderLoaded(SHADER_NAME) ? fhl::ResMgr::getShader(SHADER_NAME) : fhl::ResMgr::loadShader(fhl::shaderSrcs::coloredRect_Vertex, fhl::shaderSrcs::coloredRect_Fragment, SHADER_NAME, Shader::FromString)),
     m_color(Color::Transparent),
     m_usingOriginalShader(true)
{
   setUp();
}

void ColoredRect::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == fhl::ResMgr::getShader(SHADER_NAME) || _shader == fhl::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void ColoredRect::setLight(const Light& _light)
{
   m_shader = &fhl::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   m_shader->setLight("light", _light);
}

void ColoredRect::draw(const DrawConf & _conf) const
{
   m_shader->use();

   glm::vec4 normColor = m_color.asVec4();

   const Transform* transform = (_conf == DrawConf::Default) ? &m_transform : &_conf.transform;

   m_shader->setMat4("translation", transform->translation)
           .setMat4("rotation", transform->rotation)
           .setMat4("scale", transform->scale)
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
      fhl::ResMgr::loadShader(fhl::shaderSrcs::coloredRect_LightVertex, fhl::shaderSrcs::coloredRect_LightFragment, LIGHT_SHADER_NAME);
      LIGHT_SHADER_LOADED = true;
   }

   m_vao->bind();
   Configurator::rectShapeEbo->bind();
   m_vao->unbind();
}

}
