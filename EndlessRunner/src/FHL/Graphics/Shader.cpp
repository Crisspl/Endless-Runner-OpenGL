#include <FHL/Graphics/Shader.h>

#include <FHL/Utility/Debug.h>
#include <FHL/Maths/mathsFuncs.h>

#include <algorithm>
#include <fstream>

namespace fhl
{

	 Shader::Shader(Shader && _other)
		  : m_id(_other.m_id)
	 {
		  _other.m_id = 0;
	 }

	 Shader & Shader::operator=(Shader && _other)
	 {
		  std::swap(m_id, _other.m_id);

		  return *this;
	 }

	 Shader::Shader(const GLchar * _vert, const GLchar * _frag, SourceFrom _srcFrom)
		  : m_id(glCreateProgram())
	 {
		 GLuint vId, fId;
		 if (_srcFrom == SourceFrom::FromFile)
		 {
			 compileShaderFromFile(_vert, GL_VERTEX_SHADER, vId);
			 compileShaderFromFile(_frag, GL_FRAGMENT_SHADER, fId);
		 }
		 else
		 {
			 compileShaderFromString(_vert, GL_VERTEX_SHADER, vId);
			 compileShaderFromString(_frag, GL_FRAGMENT_SHADER, fId);
		 }

		 glLinkProgram(m_id);

		 glDetachShader(m_id, vId);
		 glDeleteShader(vId);
		 glDetachShader(m_id, fId);
		 glDeleteShader(fId);

		 GLint success;
		 GLchar infoLog[0x200];
		 glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		 if(!success)
		 {
			 glGetProgramInfoLog(m_id, 0x200, nullptr, infoLog);
			 Debug::Log() << "fhl::Shader: Linking of shader program failed:\n" << infoLog << '\n';
		 }
	 }

	 Shader::~Shader()
	 {
		 glDeleteProgram(m_id);
	 }

	 Shader & Shader::setBoolean(const GLchar * _name, const GLboolean _value)
	 {
		 return setInt(_name, _value);
	 }

	 Shader& Shader::setFloat(const GLchar* _name, const GLfloat _value)
	 {
		 use();
		 glUniform1f(glGetUniformLocation(getId(), _name), _value);
		 return *this;
	 }

	 Shader& Shader::setInt(const GLchar* _name, const GLint _value)
	 {
		 use();
		 glUniform1i(glGetUniformLocation(getId(), _name), _value);
		 return *this;
	 }

	 Shader& Shader::setVec2f(const GLchar* _name, const Vec2f & _value)
	 {
		 use();
		 glUniform2f(glGetUniformLocation(getId(), _name), _value.x(), _value.y());
		 return *this;
	 }

	 Shader& Shader::setVec3f(const GLchar* _name, const Vec3f & _value)
	 {
		 use();
		 glUniform3f(glGetUniformLocation(getId(), _name), _value.x(), _value.y(), _value.z());
		 return *this;
	 }

	 Shader& Shader::setVec4f(const GLchar* _name, const Vec4f & _value)
	 {
		 use();
		 glUniform4f(glGetUniformLocation(getId(), _name), _value.x(), _value.y(), _value.z(), _value.w());
		 return *this;
	 }

	 Shader& Shader::setColor(const GLchar* _name, const Color & _value)
	 {
		 return setVec4f(_name, _value.asVec4());
	 }

	 Shader& Shader::setMat4(const GLchar* _name, const Mat4 & _matrix)
	 {
		 use();
		 glUniformMatrix4fv(glGetUniformLocation(getId(), _name), 1, GL_FALSE, _matrix.data());
		 return *this;
	 }

	 Shader& Shader::setLight(const GLchar* _name, const Light & _light)
	 {
		 const std::string name(_name);
		 switch(_light.type)
		 {
#define COMMON_CALLS_FOR_POINT_AND_SPOT \
setVec3f((name + ".position").c_str(), _light.position); \
setFloat((name + ".linear").c_str(), _light.linear); \
setFloat((name + ".quadratic").c_str(), _light.quadratic);

			 case Light::Infinite:
				 setVec3f((name + ".direction").c_str(), _light.direction);
				 break;
			 case Light::Point:
				 COMMON_CALLS_FOR_POINT_AND_SPOT
				 break;
			 case Light::Spot:
			 {
				 const float cutOffAngle = clamp(_light.cutOffAngle, 0.f, 90.f);
				 const float outerCutOff = std::min(cutOffAngle + 20.f, 90.f);
				 COMMON_CALLS_FOR_POINT_AND_SPOT
				 setVec3f((name + ".direction").c_str(), _light.direction);
				 setFloat((name + ".cutOff").c_str(), cos(toRadians(cutOffAngle)));
				 setFloat((name + ".outerCutOff").c_str(), cos(toRadians(outerCutOff)));
			 }break;
		 }
#undef COMMON_CALLS_FOR_POINT_AND_SPOT

		 setColor((name + ".color").c_str(), _light.color);
		 setFloat((name + ".illuminance").c_str(), _light.illuminance);
		 setInt((name + ".type").c_str(), _light.type);
		 return *this;
	 }

	 Shader& Shader::setLight(const GLchar * _name, const Light & _light, size_t _num)
	 {
		 std::string name(_name);
		 name += '[' + std::to_string(_num) + ']';
		 return setLight(name.c_str(), _light);
	 }

	 Shader & Shader::setLights(const GLchar * _name, const std::vector<Light> & _lights)
	 {
		 return setLights(_name, _lights.cbegin(), _lights.cend());
	 }

	 bool Shader::operator==(const Shader & _other)
	 {
		 return m_id == _other.getId();
	 }
	 bool Shader::operator!=(const Shader & _other)
	 {
		 return m_id != _other.getId();
	 }

	 void Shader::compileShaderFromString(const GLchar * _src, GLenum _type, GLuint & _idGetter)
	 {
		 GLuint shader = _idGetter = glCreateShader(_type);
		 glShaderSource(shader, 1, &_src, nullptr);
		 glCompileShader(shader);
		 GLint success;
		 GLchar infoLog[0x200];
		 glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		 if(!success)
		 {
			 glGetShaderInfoLog(shader, 0x200, nullptr, infoLog);
			 Debug::Log() << "fhl::Shader: Failed to compile a shader:\n" << infoLog << '\n';
		 }

		 glAttachShader(m_id, shader);
	 }

	 void Shader::compileShaderFromFile(const GLchar * _path, GLenum _type, GLuint & _idGetter)
	 {
		 std::string sourceStr;
		 std::string line;
		 std::ifstream srcFile(_path);
		 while (getline(srcFile, line))
			 sourceStr += line + '\n';
		 const GLchar * source = sourceStr.c_str();

		 compileShaderFromString(source, _type, _idGetter);
	 }

} // ns
