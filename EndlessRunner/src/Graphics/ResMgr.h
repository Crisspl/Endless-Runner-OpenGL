#ifndef FHL_RESMGR_H
#define FHL_RESMGR_H

#include <map>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace fhl
{

	 class ResMgr
	 {
		  ResMgr() = delete;

	 public:
		  static Shader & loadShader(const std::string & _name, const std::string & _vert, const std::string & _frag, Shader::SourceFrom _srcFrom = Shader::FromFile);
		  static Texture & loadTexture(const std::string & _name, const std::string & _path);
		  static Texture & createTexture(const std::string & _name, Vec2i _size);

		  static Shader * getShader(const std::string & _name);
		  static Texture * getTexture(const std::string & _name);

		  template<typename _T>
		  static Shader * getDefaultSimpleShader();
		  template<typename _T>
		  static Shader * getDefaultLightShader();

		  static bool isShaderLoaded(const std::string & _name);
		  static bool isTextureLoaded(const std::string & _name);

		  static void removeShader(const std::string & _name);
		  static void removeTexture(const std::string & _name);

		  static void removeAllShaders();
		  static void removeAllTextures();

		  static void clear();

	 private:
		  static std::map<std::string, Shader> m_shaders;
		  static std::map<std::string, Texture> m_textures;
	 };

} // ns

#endif // FHL_RESMGR_H
