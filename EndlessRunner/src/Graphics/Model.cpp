#include "Model.h"

#include "../Utility/Debug.h"

namespace fhl
{

unsigned Model::m_createdNumber = 0;
bool Model::s_lightShaderLoaded = false;

Model::Model(std::string _path)
   : Litable(fhl::ResMgr::isShaderLoaded(SHADER_NAME) ? fhl::ResMgr::getShader(SHADER_NAME) : fhl::ResMgr::loadShader(fhl::shaderSrcs::model_Vertex, fhl::shaderSrcs::model_Fragment, SHADER_NAME, Shader::FromString)),
     m_usingOriginalShader(true)
{
   loadModel(_path);
   calcSize();
   m_createdNumber++;

   if(!s_lightShaderLoaded)
   {
      fhl::ResMgr::loadShader(fhl::shaderSrcs::model_LightVertex, fhl::shaderSrcs::model_LightFragment, LIGHT_SHADER_NAME, Shader::FromString);
      s_lightShaderLoaded = true;
   }
}

void Model::draw(const DrawConf & _conf) const
{
   glEnable(GL_DEPTH_TEST);

   m_shader->use();

   const Transform* transform = (_conf == DrawConf::Default) ? &m_transform : &_conf.transform;

   m_shader->setMat4("translation", transform->translation)
           .setMat4("rotation", transform->rotation)
           .setMat4("scale", transform->scale)
           .setMat4("view", Configurator::view())
           .setMat4("projection", Configurator::projection())
           .setFloat("material.shininess", 5.f);

   for(const auto& mesh : m_meshes)
      mesh.draw(*m_shader);

   Shader::unUse();

   glDisable(GL_DEPTH_TEST);
}

void Model::setShader(Shader& _shader)
{
   m_shader = &_shader;
   m_usingOriginalShader = ( _shader == fhl::ResMgr::getShader(SHADER_NAME) || _shader == fhl::ResMgr::getShader(LIGHT_SHADER_NAME));
}

void Model::setLight(const Light& _light)
{
   m_shader = &fhl::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   Litable::setLight(_light);
}

void Model::setLights(const std::initializer_list<std::reference_wrapper<Light>>& _lights)
{
   m_shader = &fhl::ResMgr::getShader(LIGHT_SHADER_NAME);
   m_usingOriginalShader = true;
   Litable::setLights(_lights);
}

void Model::setLights(std::vector<Light>& _lights)
{
	m_shader = &fhl::ResMgr::getShader(LIGHT_SHADER_NAME);
	m_usingOriginalShader = true;
	Litable::setLights(_lights);
}

void Model::loadModel(std::string _path)
{
   Assimp::Importer importer;
   const aiScene* const scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

   if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
   {
	  fhl::DebugLog << "Error loading model: " << importer.GetErrorString() << '\n';
      return;
   }

   m_directory = _path.substr(0, _path.find_last_of('/'));

   processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* _nodePtr, const aiScene* _scenePtr)
{
   for(GLuint i = 0; i < _nodePtr->mNumMeshes; i++)
   {
      aiMesh* meshPtr = _scenePtr->mMeshes[_nodePtr->mMeshes[i]];
      m_meshes.push_back(processMesh(meshPtr, _scenePtr));
   }

   for(GLuint i = 0; i < _nodePtr->mNumChildren; i++)
      processNode(_nodePtr->mChildren[i], _scenePtr);
}

Mesh Model::processMesh(aiMesh* _meshPtr, const aiScene* _scenePtr)
{
   std::vector<Mesh::Vertex> vertices;
   std::vector<GLuint> indices;
   std::vector<Mesh::Texture> textures;

   for(GLuint i = 0; i < _meshPtr->mNumVertices; i++)
   {
      Mesh::Vertex vertex;

      vertex.position.x = _meshPtr->mVertices[i].x;
      vertex.position.y = _meshPtr->mVertices[i].y;
      vertex.position.z = _meshPtr->mVertices[i].z;

      vertex.normal.x = _meshPtr->mNormals[i].x;
      vertex.normal.y = _meshPtr->mNormals[i].y;
      vertex.normal.z = _meshPtr->mNormals[i].z;

      if(_meshPtr->mTextureCoords[0])
      {
         vertex.texCoords.x = _meshPtr->mTextureCoords[0][i].x;
         vertex.texCoords.y = _meshPtr->mTextureCoords[0][i].y;
      }
      else
         vertex.texCoords = glm::vec2(0.f, 0.f);

      vertices.push_back(vertex);
   }

   for(GLuint i = 0; i < _meshPtr->mNumFaces; i++)
   {
      aiFace face = _meshPtr->mFaces[i];
      for(GLuint j = 0; j < face.mNumIndices; j++)
         indices.push_back(face.mIndices[j]);
   }

   if(_meshPtr->mMaterialIndex >= 0)
   {
      aiMaterial* materialPtr = _scenePtr->mMaterials[_meshPtr->mMaterialIndex];

      std::vector<Mesh::Texture> diffuseTexs = loadMaterialTextures(materialPtr, aiTextureType_DIFFUSE, "texture_diffuse");
      std::vector<Mesh::Texture> specularTexs = loadMaterialTextures(materialPtr, aiTextureType_SPECULAR, "texture_specular");

      textures.insert(textures.end(), diffuseTexs.begin(), diffuseTexs.end());
      textures.insert(textures.end(), specularTexs.begin(), specularTexs.end());
	  /*
	  std::cout << "diffuse:\n";
	  for (Mesh::Texture & t : diffuseTexs)
		  std::cout << t.fileName.C_Str() << '\n';
	  std::cout << "specular:\n";
	  for (Mesh::Texture & t : specularTexs)
		  std::cout << t.fileName.C_Str() << '\n';
	  */
   }

   return Mesh(vertices, indices, textures);
}

void Model::calcSize()
{
   std::vector<float> xVec, yVec, zVec;

   for(auto& mesh : m_meshes)
   {
      std::pair<float, float> minMaxX, minMaxY, minMaxZ;
      std::tie(minMaxX, minMaxY, minMaxZ) = mesh.getMinMaxCoords();

	  xVec.push_back(minMaxX.first);
	  xVec.push_back(minMaxX.second);

	  yVec.push_back(minMaxY.first);
	  yVec.push_back(minMaxY.second);

	  zVec.push_back(minMaxZ.first);
	  zVec.push_back(minMaxZ.second);
   }

   auto x = std::minmax_element(xVec.begin(), xVec.end());
   auto y = std::minmax_element(yVec.begin(), yVec.end());
   auto z = std::minmax_element(zVec.begin(), zVec.end());
   
   m_size = {
               *x.second - *x.first,
               *y.second - *y.first,
               *z.second - *z.first
            }; 
}

std::vector<Mesh::Texture> Model::loadMaterialTextures(aiMaterial* _materialPtr, aiTextureType _texType, std::string _texTypeName)
{
   std::vector<Mesh::Texture> textures;

   for(GLuint i = 0; i < _materialPtr->GetTextureCount(_texType); i++)
   {
      aiString str;
      _materialPtr->GetTexture(_texType, i, &str);
      GLboolean loaded = false;
      for(Mesh::Texture & tex : textures)
      {
         if(tex.fileName == str)
         {
            textures.push_back(tex);
            loaded = true;
            break;
         }
      }

      if(!loaded)
      {
         Mesh::Texture texture;

         std::string filePath = m_directory + '/' + str.C_Str();
         std::string modelName = 'M' + std::to_string(m_createdNumber);

         texture.id = fhl::ResMgr::loadTexture(filePath, modelName + _texTypeName + std::to_string(i)).setRepeated(true)
                                                                                                     .getId();
		 std::cout << "start id: " << fhl::ResMgr::getTexture(modelName + _texTypeName + std::to_string(i)).getId() << '\n';
		 std::cout << str.C_Str() << '\n';
         texture.type = _texTypeName;
         texture.fileName = str;
         textures.push_back(texture);
      }
   }
   return textures;
}

} // ns
