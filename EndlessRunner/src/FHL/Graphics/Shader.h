#ifndef FHL_SHADER_H
#define FHL_SHADER_H

#include <algorithm>
#include <vector>
#include <string>
#include <type_traits>
#include <iterator>

#include <FHL/GL/gl3w.h>
#include <FHL/Graphics/Color.h>
#include <FHL/Graphics/Light.h>
#include <FHL/Maths/Mat4.h>

namespace fhl { class ResMgr; }

namespace fhl
{

	 class Shader
	 {
		  friend class fhl::ResMgr;

		  template<typename, typename>
		  friend struct std::pair;

	 public:
		  enum SourceFrom
		  {
				FromFile = 0,
				FromString
		  };

	 private:
		  Shader(const Shader &) = delete;
		  Shader & operator=(const Shader &) = delete;
		  Shader(Shader && _other);
		  Shader & operator=(Shader && _other);
		  Shader(const GLchar * _vert, const GLchar * _frag, const SourceFrom _srcFrom = SourceFrom::FromFile);

		  ~Shader();

	 public:
		  void use() const { glUseProgram(m_id); }
		  static void unuse() { glUseProgram(0); }

		  GLuint getId() const { return m_id; }

		  Shader & setBoolean(const GLchar * _name, const GLboolean _value);
		  Shader & setFloat(const GLchar * _name, const GLfloat _value);
		  Shader & setInt(const GLchar * _name, const GLint _value);
		  Shader & setVec2f(const GLchar * _name, const Vec2f & _value);
		  Shader & setVec3f(const GLchar * _name, const Vec3f & _value);
		  Shader & setVec4f(const GLchar * _name, const Vec4f & _value);
		  Shader & setColor(const GLchar * _name, const Color & _value);
		  Shader & setMat4f(const GLchar * _name, const Mat4f & _matrix);

		  Shader & setLight(const GLchar * _name, const Light & _light);
		  Shader & setLight(const GLchar * _name, const Light & _light, size_t _num);
		  Shader & setLights(const GLchar * _name, const std::vector<Light> & _lights);

		  template<typename _It>
		  Shader & setLights(const GLchar * _name, _It _begin, const _It _end);

		  bool operator==(const Shader &);
		  bool operator!=(const Shader &);

	 private:
		  void compileShaderFromString(const GLchar * _src, GLenum _type, GLuint &);
		  void compileShaderFromFile(const GLchar * _path, GLenum _type, GLuint &);

	 private:
		  GLuint m_id;
	 };

	 template<typename _It>
	 Shader & Shader::setLights(const GLchar * _name, _It _begin, const _It _end)
	 {
		  static_assert(std::is_same<typename std::iterator_traits<_It>::value_type, Light>::value,
				"_begin and _end must be iterators of containers of fhl::Light objects");

		  size_t n = 0;
		  while (_begin != _end)
				setLight(_name, *(_begin++), n++);
		  return setInt("lightsCount", n);
	 }

} // ns

#endif // FHL_SHADER_H
