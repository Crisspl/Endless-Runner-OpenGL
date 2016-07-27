#include "VertexArray.h"

namespace gr
{

VertexArray::VertexArray(Mode _mode)
   : m_shader(ut::ResMgr::isShaderLoaded(SHADER_NAME) ? ut::ResMgr::getShader(SHADER_NAME) : ut::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     m_mode(_mode)
{
   setUp();
}

VertexArray& VertexArray::addVertex(Vertex _vert)
{
   m_vertices.push_back(_vert);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   return *this;
}

void VertexArray::draw() const
{
   m_shader.use();

   m_shader.setMat4("projection", Configurator::projection())
           .setMat4("view", Configurator::view());

   glBindVertexArray(m_vao);
   glDrawArrays(m_mode, 0, m_vertices.size());
   glBindVertexArray(0);

   Shader::unUse();
}

void VertexArray::setUp()
{
   glGenVertexArrays(1, &m_vao);
   glBindVertexArray(m_vao);

   glGenBuffers(1, &m_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

   glVertexAttribPointer((GLuint)AttLoc::Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray((GLuint)AttLoc::Position);

   glVertexAttribPointer((GLuint)AttLoc::Color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
   glEnableVertexAttribArray((GLuint)AttLoc::Color);

   glBindVertexArray(0);
}

} // ns
