#ifndef FHL_MODEL_H
#define FHL_MODEL_H

#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ResMgr.h"
#include "Mesh.h"
#include "Texture.h"
#include "Renderable.h"
#include "Transformable3D.h"
#include "Litable.h"
#include "UsingShader.h"

#include <iostream>

namespace fhl
{

	 class Model
		 : public Renderable,
			public Transformable3D,
			public Litable,
		   public UsingShader
	 {
	 public:
		  explicit Model(std::string _path);
		  void render(const RenderConf & _conf) const override;

	 private:
		  void loadModel(std::string _path);
		  void processNode(aiNode* _nodePtr, const aiScene* _scenePtr);
		  Mesh processMesh(aiMesh* _meshPtr, const aiScene* _scenePtr);
		  void calcSize();

		  std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* _materialPtr, aiTextureType _texType, std::string _texTypeName);

	 private:
		  std::vector<Mesh> m_meshes;
		  std::string m_directory;

		  bool m_usingOriginalShader;

		  static unsigned m_createdNumber;

		  constexpr static const char * simpleShaderName = "_FHL_modelSimpleShader";
		  constexpr static const char * lightShaderName = "_FHL_modelLightShader";
	 };

} // ns

#endif // FHL_MODEL_H
