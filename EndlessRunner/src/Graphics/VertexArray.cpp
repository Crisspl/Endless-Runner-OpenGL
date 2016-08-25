#include "VertexArray.h"

namespace fhl
{

VertexArray::VertexArray(Mode _mode)
   : m_shader(fhl::ResMgr::isShaderLoaded(SHADER_NAME) ? fhl::ResMgr::getShader(SHADER_NAME) : fhl::ResMgr::loadShader(VSHADER_PATH, FSHADER_PATH, SHADER_NAME)),
     m_mode(_mode),
	 m_vao(new Vao())
{
   setUp();
}

VertexArray& VertexArray::addVertex(Vertex _vert)
{
   m_vertices.push_back(_vert);

   auto buffer = m_vao->getBuffer("vertexBuffer");
   buffer->bind();
   buffer->setData(sizeof(Vertex) * m_vertices.size(), &m_vertices[0]);
   buffer->unbind();

   return *this;
}

void VertexArray::draw(const DrawConf &) const
{
   m_shader.use();

   m_shader.setMat4("projection", Configurator::projection())
           .setMat4("view", Configurator::view());

   m_vao->bind();
   glDrawArrays(m_mode, 0, m_vertices.size());
   m_vao->unbind();

   Shader::unUse();
}

void VertexArray::setUp()
{
	Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

	m_vao->bind();

	m_vao->addBuffer("vertexBuffer", buffer);

	buffer->bind();

	glVertexAttribPointer((GLuint)AttLoc::Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray((GLuint)AttLoc::Position);

	glVertexAttribPointer((GLuint)AttLoc::Color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray((GLuint)AttLoc::Color);

	m_vao->unbind();
}

} // ns
