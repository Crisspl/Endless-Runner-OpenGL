#include "ResMgr.h"

namespace fhl
{

std::map<std::string, fhl::Shader> ResMgr::m_shaders;
std::map<std::string, fhl::Texture> ResMgr::m_textures;

fhl::Shader& ResMgr::loadShader(std::string _vertPath, std::string _fragPath, std::string _name)
{
   m_shaders.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_vertPath, _fragPath));
   return m_shaders[_name];
}

fhl::Texture& ResMgr::loadTexture(std::string _path, std::string _name)
{
   m_textures.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_path));
   return m_textures[_name];
}

fhl::Texture& ResMgr::loadTexture(glm::tvec2<GLint> _size, std::string _name)
{
   m_textures[_name] = fhl::Texture(_size);
   return m_textures[_name];
}

fhl::Shader& ResMgr::getShader(std::string _name)
{
   return m_shaders[_name];
}

fhl::Texture& ResMgr::getTexture(std::string _name)
{
   return m_textures[_name];
}

bool ResMgr::isShaderLoaded(std::string _name)
{
	return m_shaders.find(_name) != m_shaders.end();
}

bool ResMgr::isTextureLoaded(std::string _name)
{
	return m_textures.find(_name) != m_textures.end();
}

void ResMgr::clear()
{
   for(auto& el : m_shaders)
      glDeleteProgram(el.second.getId());
   for(auto& el : m_textures)
      glDeleteTextures(1, &el.second.getId());
}

} // ns
