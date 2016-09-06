#include "Shader.h"

#include "../Utility/Debug.h"

namespace fhl
{

Shader::Shader(const GLchar * _vert, const GLchar * _frag, SourceFrom _srcFrom)
      : m_shaderProgram(glCreateProgram())
{
	if (_srcFrom == SourceFrom::FromFile)
	{
		compileShaderFromFile(_vert, GL_VERTEX_SHADER);
		compileShaderFromFile(_frag, GL_FRAGMENT_SHADER);
	}
	else
	{
		compileShaderFromString(_vert, GL_VERTEX_SHADER);
		compileShaderFromString(_frag, GL_FRAGMENT_SHADER);
	}

   glLinkProgram(m_shaderProgram);

   GLint success;
   GLchar infoLog[0x200];
   glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
   if(!success)
   {
      glGetProgramInfoLog(m_shaderProgram, 0x200, nullptr, infoLog);
      fhl::DebugLog << "Linking of shader program failed.\n" << infoLog << '\n';
   }
}

const Shader& Shader::setFloat(const GLchar* _name, const GLfloat _value) const
{
   use();
   glUniform1f(glGetUniformLocation(getId(), _name), _value);
   return *this;
}

const Shader& Shader::setInt(const GLchar* _name, const GLint _value) const
{
   use();
   glUniform1i(glGetUniformLocation(getId(), _name), _value);
   return *this;
}

const Shader& Shader::setVec2f(const GLchar* _name, const glm::vec2& _value) const
{
   use();
   glUniform2f(glGetUniformLocation(getId(), _name), _value.x, _value.y);
   return *this;
}

const Shader& Shader::setVec3f(const GLchar* _name, const glm::vec3& _value) const
{
   use();
   glUniform3f(glGetUniformLocation(getId(), _name), _value.x, _value.y, _value.z);
   return *this;
}

const Shader& Shader::setVec4f(const GLchar* _name, const glm::vec4& _value) const
{
   use();
   glUniform4f(glGetUniformLocation(getId(), _name), _value.x, _value.y, _value.z, _value.w);
   return *this;
}

const Shader& Shader::setColor(const GLchar* _name, const Color& _value) const
{
   glm::vec4 val = _value.asVec4();
   return setVec4f(_name, val);
}

const Shader& Shader::setMat4(const GLchar* _name, const glm::mat4& _matrix) const
{
   use();
   glUniformMatrix4fv(glGetUniformLocation(getId(), _name), 1, GL_FALSE, glm::value_ptr(_matrix));
   return *this;
}

const Shader& Shader::setLight(const GLchar* _name, const Light& _light) const
{
   std::string name(_name);
   switch(_light.type)
   {
      case Light::Directional:
         setVec3f((name + ".direction").c_str(), _light.direction);
         break;
      case Light::Point:
         setVec3f((name + ".position").c_str(), _light.position);
         setFloat((name + ".linear").c_str(), _light.linear);
         setFloat((name + ".quadratic").c_str(), _light.quadratic);
         break;
      case Light::Spot:
      {
         float cutOffAngle = std::min(_light.cutOffAngle, 90.f);
         float outerCutOff = std::min(cutOffAngle + 20.f, 90.f);
         setVec3f((name + ".position").c_str(), _light.position);
         setVec3f((name + ".direction").c_str(), _light.direction);
         setFloat((name + ".cutOff").c_str(), cos(glm::radians(cutOffAngle)));
         setFloat((name + ".outerCutOff").c_str(), cos(glm::radians(outerCutOff)));
      }
         break;
   }
   setColor((name + ".color").c_str(), _light.color);
   setFloat((name + ".illuminance").c_str(), _light.illuminance);
   setInt((name + ".type").c_str(), _light.type);
   return *this;
}

const Shader& Shader::setLight(const GLchar* _name, const Light& _light, size_t _num) const
{
   std::string name(_name);
   name += '[' + std::to_string(_num) + ']';
   return setLight(name.c_str(), _light);
}

const Shader& Shader::setLights(const GLchar* _name, const std::initializer_list<std::reference_wrapper<Light>>& _lights) const
{
   size_t n = 0;
   for(auto& l : _lights)
      setLight(_name, l, n++);
   return setInt("lightsCount", _lights.size());
}

const Shader & Shader::setLights(const GLchar * _name, std::vector<Light>& _lights) const
{
	size_t n = 0;
	for (auto& l : _lights)
		setLight(_name, l, n++);
	return setInt("lightsCount", _lights.size());
}

bool Shader::operator==(const Shader& _outer)
{
   return m_shaderProgram == _outer.getId();
}
bool Shader::operator!=(const Shader& _outer)
{
   return m_shaderProgram != _outer.getId();
}

void Shader::compileShaderFromString(const GLchar * _src, GLenum _type)
{
   GLuint shader = glCreateShader(_type);
   glShaderSource(shader, 1, &_src, nullptr);
   glCompileShader(shader);
   GLint success;
   GLchar infoLog[0x200];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
   if(!success)
   {
      glGetShaderInfoLog(shader, 0x200, nullptr, infoLog);
      fhl::DebugLog << "Failed to compile a shader \n" << infoLog << '\n';
   }

   glAttachShader(m_shaderProgram, shader);
   glDeleteShader(shader);
}

void Shader::compileShaderFromFile(const GLchar * _path, GLenum _type)
{
	std::string sourceStr;
	std::string line;
	std::ifstream srcFile(_path);
	while (getline(srcFile, line))
		sourceStr += line + '\n';
	const GLchar * source = sourceStr.c_str();

	compileShaderFromString(source, _type);
}

} // ns
