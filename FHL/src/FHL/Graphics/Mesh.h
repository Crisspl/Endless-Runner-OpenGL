#ifndef FHL_MESH_H
#define FHL_MESH_H

#include <string>
#include <vector>
#include <tuple>

#include <FHL/GL/gl3w.h>
#include <FHL/Graphics/Buffer.h>
#include <FHL/Maths/vectors.h>


namespace fhl 
{ 
	 class Model;
	 class ModelData;

namespace internal
{

	class FHL_API Mesh
	{
		using tuple3pair_t = std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>>;
		friend class Model;
		friend class ModelData;

		struct Vertex
		{
			Vec3f position;
			Vec3f normal;
			Vec2f texCoords;
		};

		struct Texture
		{
			enum class Type
			{
				Diffuse,
				Specular
			};

			static std::string typeToString(Type _t)
			{
				switch (_t)
				{
				case Type::Diffuse: return "texture_diffuse";
				case Type::Specular: return "texture_specular";
				default: return{};
				}
			}

			GLuint id;
			Type type;
			std::string fileName;
		};

	public:
		Mesh(const std::vector<Mesh::Vertex> & _vertices, const std::vector<GLuint> & _indices, std::vector<Mesh::Texture> _textures);

	private:
		void setUp(const std::vector<Mesh::Vertex> & _vertices, const std::vector<GLuint> & _indices);

		std::vector<Mesh::Texture> textures;
		std::size_t indicesCount;
		tuple3pair_t minMaxVerts;
		Buffer vbo, ebo;
	};

}} // ns

#endif // FHL_MESH_H
