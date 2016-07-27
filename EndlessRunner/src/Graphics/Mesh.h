#ifndef MESH_H
#define MESH_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Configurator.h"
#include "Shader.h"

namespace gr
{

class Mesh
{
   using T_tuple3Vec2 = std::tuple<glm::vec2, glm::vec2, glm::vec2>;

public:
   struct Vertex
   {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 texCoords;
   };

   struct Texture
   {
      GLuint id;
      std::string type;
      aiString fileName;
   };

public:
   Mesh(std::vector<Mesh::Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Mesh::Texture> _textures);

   void draw(Shader& _shader) const;
   T_tuple3Vec2 getMinMaxCoords();

private:
   void setUp();

public:
   std::vector<Mesh::Vertex> m_vertices;
   std::vector<GLuint> m_indices;
   std::vector<Mesh::Texture> m_textures;

private:
   GLuint m_vao, m_vbo, m_ebo;
};

} // ns

#endif // MESH_H
