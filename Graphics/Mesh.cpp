#include "Mesh.h"

namespace gr
{

Mesh::Mesh(std::vector<Mesh::Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Mesh::Texture> _textures)
   : m_vertices(_vertices),
     m_indices(_indices),
     m_textures(_textures)
{
   setUp();
}

void Mesh::draw(Shader& _shader) const
{
   GLuint diffuseNr, specularNr;

   _shader.use();

   for(GLuint i = 0; i < m_textures.size(); i++)
   {
      glActiveTexture(GL_TEXTURE0 + i);

      std::string number;
      std::string name = m_textures[i].type;

      if(name == "texture_diffuse")
         number = std::to_string(diffuseNr++);
      else if(name == "texture_specular")
         number = std::to_string(specularNr++);

      _shader.setInt(("material." + name + number).c_str(), i);
      glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
   }

   glBindVertexArray(m_vao);
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

   glBindVertexArray(0);

   for(GLuint i = 0; i < m_textures.size(); i++)
   {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, 0);
   }
   glActiveTexture(GL_TEXTURE0);
}

std::tuple<glm::vec2, glm::vec2, glm::vec2>
   Mesh::getMinMaxCoords()
{
   auto compX = [](Vertex& a, Vertex& b)->bool { return a.position.x < b.position.x; };
   auto compY = [](Vertex& a, Vertex& b)->bool { return a.position.y < b.position.y; };
   auto compZ = [](Vertex& a, Vertex& b)->bool { return a.position.z < b.position.z; };

   auto minMaxX = std::minmax_element(m_vertices.begin(), m_vertices.end(), compX);
   auto minMaxY = std::minmax_element(m_vertices.begin(), m_vertices.end(), compY);
   auto minMaxZ = std::minmax_element(m_vertices.begin(), m_vertices.end(), compZ);

   return std::make_tuple
               (
                  glm::vec2(minMaxX.first->position.x, minMaxX.second->position.x),
                  glm::vec2(minMaxY.first->position.y, minMaxY.second->position.y),
                  glm::vec2(minMaxZ.first->position.z, minMaxZ.second->position.z)
               );
}

void Mesh::setUp()
{
   glGenVertexArrays(1, &m_vao);
   glGenBuffers(1, &m_vbo);
   glGenBuffers(1, &m_ebo);

   glBindVertexArray(m_vao);

   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
   glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
   glEnableVertexAttribArray(1);

   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
   glEnableVertexAttribArray(2);

   glBindVertexArray(0);
}

}
