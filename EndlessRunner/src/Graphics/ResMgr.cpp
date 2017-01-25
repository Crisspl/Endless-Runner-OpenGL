#include "ResMgr.h"

#include "ColoredRect.h"
#include "Model.h"
#include "Sprite.h"
#include "VertexArray.h"

namespace fhl
{

	 std::map<std::string, Shader> ResMgr::m_shaders;
	 std::map<std::string, Texture> ResMgr::m_textures;

	 Shader & ResMgr::loadShader(std::string _name, std::string _vert, std::string _frag, Shader::SourceFrom _srcFrom)
	 {
		 m_shaders.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_vert.c_str(), _frag.c_str(), _srcFrom));
		 return *getShader(_name);
	 }

	 Texture & ResMgr::loadTexture(std::string _name, std::string _path)
	 {
		 m_textures.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_path));
		 return *getTexture(_name);
	 }

	 Texture & ResMgr::loadTexture(std::string _name, Vec2i _size)
	 {
		 m_textures.emplace(std::piecewise_construct, std::make_tuple(_name), std::make_tuple(_size));
		 return *getTexture(_name);
	 }

	 Shader * ResMgr::getShader(std::string _name)
	 {
		 return isShaderLoaded(_name) ? &m_shaders.find(_name)->second : nullptr;
	 }

	 Texture * ResMgr::getTexture(std::string _name)
	 {
		 return isTextureLoaded(_name) ? &m_textures.find(_name)->second : nullptr;
	 }

	 template<typename _T>
	 Shader * ResMgr::getDefaultSimpleShader()
	 {
		  return isShaderLoaded(_T::simpleShaderName) ? getShader(_T::simpleShaderName) : nullptr;
	 }

	 template Shader * ResMgr::getDefaultSimpleShader<ColoredRect>();
	 template Shader * ResMgr::getDefaultSimpleShader<Model>();
	 template Shader * ResMgr::getDefaultSimpleShader<Sprite>();
	 template Shader * ResMgr::getDefaultSimpleShader<VertexArray>();

	 template<typename _T>
	 Shader * ResMgr::getDefaultLightShader()
	 {
		  return isShaderLoaded(_T::lightShaderName) ? getShader(_T::lightShaderName) : nullptr;
	 }

	 template Shader * ResMgr::getDefaultLightShader<ColoredRect>();
	 template Shader * ResMgr::getDefaultLightShader<Model>();
	 template Shader * ResMgr::getDefaultLightShader<Sprite>();

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
