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
   static Shader & loadShader(std::string _vert, std::string _frag, std::string _name, Shader::SourceFrom _srcFrom = Shader::FromFile);
   static Texture & loadTexture(std::string _path, std::string _name);
   static Texture & loadTexture(Vec2i _size, std::string _name);

   static Shader & getShader(std::string _name);
   static Texture & getTexture(std::string _name);

   static bool isShaderLoaded(std::string _name);
   static bool isTextureLoaded(std::string _name);

   static void removeShader(std::string _name);
   static void removeTexture(std::string _name);

   static void clear();

private:
   static std::map<std::string, fhl::Shader> m_shaders;
   static std::map<std::string, fhl::Texture> m_textures;
};

} // ns

#endif // FHL_RESMGR_H
