#ifndef RESMGR_H
#define RESMGR_H

#include <map>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace fhl
{

class ResMgr final
{
   ResMgr() = delete;

public:
   static fhl::Shader& loadShader(std::string _vert, std::string _frag, std::string _name, Shader::SourceFrom _srcFrom = Shader::FromFile);
   static fhl::Texture& loadTexture(std::string _path, std::string _name);
   static fhl::Texture& loadTexture(glm::tvec2<GLint> _size, std::string _name);

   static fhl::Shader& getShader(std::string _name);
   static fhl::Texture& getTexture(std::string _name);

   static bool isShaderLoaded(std::string _name);
   static bool isTextureLoaded(std::string _name);

   static void clear();

private:
   static std::map<std::string, fhl::Shader> m_shaders;
   static std::map<std::string, fhl::Texture> m_textures;
};

} // ns

#endif // RESMGR_H
