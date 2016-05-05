#pragma once

#include <map>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace ut
{

class ResMgr final
{
   ResMgr() = delete;

public:
   static gr::Shader& loadShader(std::string _vertPath, std::string _fragPath, std::string _name);
   static gr::Texture& loadTexture(std::string _path, std::string _name);
   static gr::Texture& loadTexture(glm::tvec2<GLint> _size, std::string _name);

   static gr::Shader& getShader(std::string _name);
   static gr::Texture& getTexture(std::string _name);

   static bool isShaderLoaded(std::string _name);
   static bool isTextureLoaded(std::string _name);

   static void clear();

private:
   static std::map<std::string, gr::Shader> m_shaders;
   static std::map<std::string, gr::Texture> m_textures;
};

} // ns
