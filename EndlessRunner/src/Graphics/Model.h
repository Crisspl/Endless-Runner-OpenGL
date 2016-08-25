#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Utility/ResMgr.h"
#include "Mesh.h"
#include "Texture.h"
#include "Drawable.h"
#include "Transformable3D.h"
#include "Litable.h"

namespace fhl
{

class Model
   : public Drawable,
     public Transformable3D,
     public Litable
{
public:
   explicit Model(std::string _path);
   void draw(const DrawConf &) const override;

   void setShader(Shader& _shader = fhl::ResMgr::getShader(SHADER_NAME)) override;
   void setLight(const Light& _light) override;
   void setLights(const std::initializer_list<std::reference_wrapper<Light>>& _lights) override;
   void setLights(std::vector<Light> & _lights) override;

private:
   void loadModel(std::string _path);
   void processNode(aiNode* _nodePtr, const aiScene* _scenePtr);
   Mesh processMesh(aiMesh* _meshPtr, const aiScene* _scenePtr);
   void calcSize();

   std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* _materialPtr, aiTextureType _texType, std::string _texTypeName);

private:
   std::vector<Mesh> m_meshes;
   std::string m_directory;

   glm::vec3 m_lightPos;

   bool m_usingOriginalShader;

   static unsigned m_createdNumber;
   static bool s_lightShaderLoaded;

   constexpr static const char* SHADER_NAME = "modelShader";
   constexpr static const char* VSHADER_PATH = "Graphics/Shaders/model_vs.glsl";
   constexpr static const char* FSHADER_PATH = "Graphics/Shaders/model_fs.glsl";

   constexpr static const char* LIGHT_SHADER_NAME = "modelLightShader";
   constexpr static const char* LIGHT_VSHADER_PATH = "Graphics/Shaders/modelLight_vs.glsl";
   constexpr static const char* LIGHT_FSHADER_PATH = "Graphics/Shaders/modelLight_fs.glsl";
};

} // ns

#endif // MODEL_H
