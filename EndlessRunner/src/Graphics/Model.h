#ifndef FHL_MODEL_H
#define FHL_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Vao.h"
#include "Renderable.h"
#include "Transformable3D.h"
#include "Litable.h"
#include "UsingShader.h"

namespace fhl
{
	 class ResMgr;

	 class Model
		 : public Renderable,
			public Transformable3D,
			public Litable,
		   public UsingShader
	 {
		  friend class ResMgr;

		  enum AttrLoc : GLuint
		  {
				Position = 0,
				Normal,
				TexCoord
		  };

	 public:
		  explicit Model(const std::string & _path);

		  void render(const RenderConf & _conf) const override;
		  Vec3f getSize() const { return m_size; }

	 private:
		  void renderMeshes() const;

		  void loadModel(const std::string & _path);
		  void processNode(aiNode * _nodePtr, const aiScene * _scenePtr);
		  internal::Mesh processMesh(aiMesh * _meshPtr, const aiScene * _scenePtr);
		  void calcSize();
		  void setUp(const std::string & _path);

		  std::vector<internal::Mesh::Texture> loadMaterialTextures(aiMesh * _mesh, aiMaterial * _materialPtr, aiTextureType _texType, internal::Mesh::Texture::Type _texTypeName);

	 private:
		  std::vector<internal::Mesh> m_meshes;
		  std::vector<Vao> m_vaos;
		  std::string m_directory;
		  std::size_t m_meshCount;
		  Vec3f m_size;

		  static std::size_t s_createdNumber;

		  constexpr static const char * simpleShaderName = "_FHL_modelSimpleShader";
		  constexpr static const char * lightShaderName = "_FHL_modelLightShader";
	 };

} // ns

#endif // FHL_MODEL_H
