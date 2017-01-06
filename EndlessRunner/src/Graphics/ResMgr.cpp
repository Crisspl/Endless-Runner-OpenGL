#include "ResMgr.h"

namespace fhl
{

	 std::map<std::string, Shader> ResMgr::m_shaders;
	 std::map<std::string, Texture> ResMgr::m_textures;

	 Shader & ResMgr::loadShader(std::string _vert, std::string _frag, std::string _name, Shader::SourceFrom _srcFrom)
	 {
		 m_shaders.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_vert.c_str(), _frag.c_str(), _srcFrom));
		 return getShader(_name);
	 }

	 Texture & ResMgr::loadTexture(std::string _path, std::string _name)
	 {
		 m_textures.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_path));
		 return getTexture(_name);
	 }

	 Texture & ResMgr::loadTexture(Vec2i _size, std::string _name)
	 {
		 m_textures.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_size));
		 return getTexture(_name);
	 }

	 Shader & ResMgr::getShader(std::string _name)
	 {
		 return m_shaders.find(_name)->second;
	 }

	 Shader & ResMgr::getLoadShader(std::string _name, std::string _vert, std::string _frag, Shader::SourceFrom _srcFrom)
	 {
		  return isShaderLoaded(_name) ? getShader(_name) : loadShader(_vert, _frag, _name, _srcFrom);
	 }

	 Texture & ResMgr::getTexture(std::string _name)
	 {
		 return m_textures.find(_name)->second;
	 }

	 bool ResMgr::isShaderLoaded(std::string _name)
	 {
		 return m_shaders.find(_name) != m_shaders.end();
	 }

	 bool ResMgr::isTextureLoaded(std::string _name)
	 {
		 return m_textures.find(_name) != m_textures.end();
	 }

	 void ResMgr::removeShader(std::string _name)
	 {
		 m_shaders.erase(_name);
	 }

	 void ResMgr::removeTexture(std::string _name)
	 {
		 m_textures.erase(_name);
	 }

	 void ResMgr::clear()
	 {
		 m_textures.clear();
		 m_shaders.clear();
	 }

} // ns
