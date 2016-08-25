#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <memory>

#include "Drawable.h"
#include "../Utility/ResMgr.h"
#include "Vertex.h"
#include "Shader.h"
#include "Configurator.h"
#include "Vao.h"

namespace fhl
{

class VertexArray
   : public Drawable
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

   void draw(const DrawConf &) const override;

   Vertex operator[](unsigned _i) const { return m_vertices[_i]; }
   Vertex& operator[](unsigned _i) { return m_vertices[_i]; }

   VertexArray& setMode(Mode _mode) { m_mode = _mode; return *this; }
   VertexArray& addVertex(Vertex _vert);

private:
   void setUp();

private:
   Shader& m_shader;
   GLenum m_mode;
   std::vector<Vertex> m_vertices;

   std::shared_ptr<Vao> m_vao;

   constexpr static const char* SHADER_NAME = "arrayShader";
   constexpr static const char* VSHADER_PATH = "Graphics/Shaders/array_vs.glsl";
   constexpr static const char* FSHADER_PATH = "Graphics/Shaders/array_fs.glsl";
};

} // ns

#endif // VERTEXARRAY_H
