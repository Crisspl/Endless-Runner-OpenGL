#ifndef FHL_SHADER_H
#define FHL_SHADER_H

#include <GL/glew.h>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Texture.h"
#include "Color.h"
#include "Light.h"
#include "ShaderSrcs.h"
#include "../Maths/Mat4.h"

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
		 Shader() = delete;
		 Shader(const GLchar * _vert, const GLchar * _frag, const SourceFrom _srcFrom = SourceFrom::FromFile);

		 ~Shader();

	 public:
		 void use() const { glUseProgram(m_shaderProgram); }
		 static void unUse() { glUseProgram(0); }

		 GLuint getId() const { return m_shaderProgram; }

		 const Shader & setFloat(const GLchar* _name, const GLfloat _value) const;
		 const Shader & setInt(const GLchar* _name, const GLint _value) const;
		 const Shader & setVec2f(const GLchar* _name, const Vec2f& _value) const;
		 const Shader & setVec3f(const GLchar* _name, const Vec3f& _value) const;
		 const Shader & setVec4f(const GLchar* _name, const Vec4f& _value) const;
		 const Shader & setColor(const GLchar* _name, const Color& _value) const;
		 const Shader & setMat4(const GLchar* _name, const Mat4& _matrix) const;

		 const Shader & setLight(const GLchar* _name, const Light& _light) const;
		 const Shader & setLight(const GLchar* _name, const Light& _light, size_t _num) const;
		 const Shader & setLights(const GLchar* _name, const std::initializer_list<std::reference_wrapper<Light>>& _lights) const;
		 const Shader & setLights(const GLchar* _name, std::vector<Light> & _lights) const;

		 bool operator==(const Shader &);
		 bool operator!=(const Shader &);

	 private:
		 void compileShaderFromString(const GLchar * _src, GLenum _type, GLuint &);
		 void compileShaderFromFile(const GLchar * _path, GLenum _type, GLuint &);

	 private:
		 GLuint m_shaderProgram;
	 };

} // ns

#endif // FHL_SHADER_H
