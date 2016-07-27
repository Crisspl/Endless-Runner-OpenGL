#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <initializer_list>
#include <functional>

#include "Texture.h"
#include "Color.h"
#include "Light.h"

namespace ut { class ResMgr; }

namespace gr
{

class Shader
{
   friend class ut::ResMgr;

   template<class A, class B>
      friend struct std::pair;
private:
   Shader() = default;
   Shader(std::string _vPath, std::string _fPath);

public:
   void use() const { glUseProgram(m_shaderProgram); }
   static void unUse() { glUseProgram(0); }

   GLuint getId() const { return m_shaderProgram; }

   const Shader& setFloat(const GLchar* _name, const GLfloat _value) const;
   const Shader& setInt(const GLchar* _name, const GLint _value) const;
   const Shader& setVec2f(const GLchar* _name, const glm::vec2& _value) const;
   const Shader& setVec3f(const GLchar* _name, const glm::vec3& _value) const;
   const Shader& setVec4f(const GLchar* _name, const glm::vec4& _value) const;
   const Shader& setColor(const GLchar* _name, const Color& _value) const;
   const Shader& setMat4(const GLchar* _name, const glm::mat4& _matrix) const;
   const Shader& setLight(const GLchar* _name, const Light& _light) const;
   const Shader& setLight(const GLchar* _name, const Light& _light, int _num) const;
   const Shader& setLights(const GLchar* _name, const std::initializer_list<std::reference_wrapper<Light>>& _lights) const;

   bool operator==(const Shader&);
   bool operator!=(const Shader&);

private:
   void compileShader(std::string _path, GLenum _type);

private:
   GLuint m_shaderProgram;
};

} // gr

#endif // SHADER_H
