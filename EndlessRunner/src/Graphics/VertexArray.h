#ifndef FHL_VERTEXARRAY_H
#define FHL_VERTEXARRAY_H

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <initializer_list>

#include "Renderable.h"
#include "ResMgr.h"
#include "Vertex.h"
#include "Shader.h"
#include "Configurator.h"
#include "Vao.h"

namespace fhl
{

	 class VertexArray
		 : public Renderable
	 {
	 public:
		  enum Mode
		  {
				Points = GL_POINTS,
				LineStrip = GL_LINE_STRIP,
				LineLoop = GL_LINE_LOOP,
				Lines = GL_LINES,
				LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
				LinesAdjacency = GL_LINES_ADJACENCY,
				TriangleStrip = GL_TRIANGLE_STRIP,
				TriangleFan = GL_TRIANGLE_FAN,
				Triangles = GL_TRIANGLES,
				TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
				TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
				Patches = GL_PATCHES
		 };

	 private:
		  enum class AttLoc : GLuint
		  {
				Position,
				Color
		  };

	 public:
		  explicit VertexArray(Mode _mode);

		  void render(const RenderConf &) const override;

		  Vertex operator[](unsigned _i) const { return m_vertices[_i]; }
		  Vertex & operator[](unsigned _i) { return m_vertices[_i]; }

		  VertexArray & setMode(Mode _mode) { m_mode = _mode; return *this; }

		  VertexArray & addVertex(Vertex _vert);
		  VertexArray & addVertices(std::initializer_list<Vertex> _v);

	 private:
		  void setUp();
		  void updateArray();

	 private:
		  Shader & m_shader;
		  GLenum m_mode;
		  std::vector<Vertex> m_vertices;

		  std::shared_ptr<Vao> m_vao;

		  constexpr static const char* SHADER_NAME = "arrayShader";
	 };

} // ns

#endif // FHL_VERTEXARRAY_H
