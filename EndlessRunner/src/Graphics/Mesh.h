#ifndef FHL_MESH_H
#define FHL_MESH_H

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
#include "../Utility/Debug.h"

namespace fhl
{

	 class Mesh
	 {
		 using T_tuple3pair = std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>>;

	 public:
		 struct Vertex
		 {
			 Vec3f position;
			 Vec3f normal;
			 Vec2f texCoords;
		 };

		 struct Texture
		 {
			 GLuint id;
			 std::string type;
			 aiString fileName;
		 };

	 public:
		 Mesh(std::vector<Mesh::Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Mesh::Texture> _textures);

		 void render(Shader& _shader) const;
		 T_tuple3pair getMinMaxCoords();

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

#endif // FHL_MESH_H
