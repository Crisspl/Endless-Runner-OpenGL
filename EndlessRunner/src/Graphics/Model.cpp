#include "Model.h"

#include <utility>

#include "../Utility/Debug.h"
#include "ResMgr.h"

namespace fhl
{

	 std::size_t Model::s_createdNumber{0};

	 Model::Model(const std::string & _path)
		 : UsingShader(&ResMgr::loadShader(simpleShaderName, shaderSrcs::model_Vertex, shaderSrcs::model_Fragment, Shader::FromString),
						   &ResMgr::loadShader(lightShaderName, shaderSrcs::model_LightVertex, shaderSrcs::model_LightFragment, Shader::FromString)),
		  m_directory(_path.substr(0, _path.find_last_of('/'))),
		  m_meshCount{0}
	 {
		 setUp(_path);
		 s_createdNumber++;
	 }

	 void Model::render(const RenderConf & _conf) const
	 {
		  if (!getShader())
				return;

		 glEnable(GL_DEPTH_TEST);

		 Shader & shader = *getShader();
		 shader.use();

		 bool useCustomConf = _conf != RenderConf::Default;

		 const auto & lights = useCustomConf ? _conf.lights : getLights();

		 shader.setMat4("mvp", useCustomConf ? _conf.matrices.mvp : getMVP())
			  .setMat4("model", useCustomConf ? _conf.matrices.transform : getTransform())
			  .setFloat("material.shininess", 5.f)
			  .setLights("light", lights.cbegin(), lights.cend());

		 renderMeshes();

		 Shader::unUse();

		 glDisable(GL_DEPTH_TEST);
	 }

	 void Model::renderMeshes() const
	 {
		  using MeshTexture = internal::Mesh::Texture;

		  for (int i = 0; i < m_meshes.size(); i++)
		  {
				GLbyte diffuseNr = 1, specularNr = 1;

				for (int j = 0; j < m_meshes[i].textures.size(); j++)
				{
					 glActiveTexture(GL_TEXTURE0 + j);

					 const auto & texture = m_meshes[i].textures[j];

					 const std::string name = MeshTexture::typeToString(texture.type);
					 const char number = (texture.type == MeshTexture::Type::Diffuse ? diffuseNr++ : specularNr++) + '0';

					 getShader()->setInt(("material." + name + number).c_str(), i);
					 glBindTexture(GL_TEXTURE_2D, texture.id);
				}

				m_vaos[i].bind();
				glDrawElements(GL_TRIANGLES, m_meshes[i].indicesCount, GL_UNSIGNED_INT, 0);
				m_vaos[i].unbind();

				for (GLuint j = 0; j < m_meshes[i].textures.size(); j++)
				{
					 glActiveTexture(GL_TEXTURE0 + j);
					 glBindTexture(GL_TEXTURE_2D, 0);
				}
				glActiveTexture(GL_TEXTURE0);
		  }
	 }

	 void Model::loadModel(const std::string & _path)
	 {
		 Assimp::Importer importer;
		 const aiScene * const scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		 if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		 {
				fhl::DebugLog << "Error loading model: " << importer.GetErrorString() << '\n';
				return;
		 }
		 processNode(scene->mRootNode, scene);
	 }

	 void Model::processNode(aiNode * _nodePtr, const aiScene * _scenePtr)
	 {
		 for(GLuint i = 0; i < _nodePtr->mNumMeshes; i++)
		 {
			 aiMesh * meshPtr = _scenePtr->mMeshes[_nodePtr->mMeshes[i]];
			 m_meshes.push_back(processMesh(meshPtr, _scenePtr));
		 }

		 for(GLuint i = 0; i < _nodePtr->mNumChildren; i++)
			 processNode(_nodePtr->mChildren[i], _scenePtr);
	 }

	 internal::Mesh Model::processMesh(aiMesh * _meshPtr, const aiScene * _scenePtr)
	 {
		 std::vector<internal::Mesh::Vertex> vertices;
		 std::vector<GLuint> indices;
		 std::vector<internal::Mesh::Texture> textures;

		 vertices.reserve(_meshPtr->mNumVertices);
		 for(GLuint i = 0; i < _meshPtr->mNumVertices; i++)
		 {
			 internal::Mesh::Vertex vertex;
			 vertex.position = { _meshPtr->mVertices[i].x, _meshPtr->mVertices[i].y, _meshPtr->mVertices[i].z };
			 vertex.normal = { _meshPtr->mNormals[i].x, _meshPtr->mNormals[i].y, _meshPtr->mNormals[i].z };

			 if(_meshPtr->mTextureCoords[0])
					 vertex.texCoords = { _meshPtr->mTextureCoords[0][i].x, _meshPtr->mTextureCoords[0][i].y };
			 else
					 vertex.texCoords = Vec2f::zero();

			 vertices.push_back(vertex);
		 }

		 for(GLuint i = 0; i < _meshPtr->mNumFaces; i++)
		 {
			 const aiFace & face = _meshPtr->mFaces[i];
			 for(GLuint j = 0; j < face.mNumIndices; j++)
				 indices.push_back(face.mIndices[j]);
		 }

		 if(_meshPtr->mMaterialIndex >= 0)
		 {
			 aiMaterial* materialPtr = _scenePtr->mMaterials[_meshPtr->mMaterialIndex];

			 std::vector<internal::Mesh::Texture> diffuseTexs = loadMaterialTextures(_meshPtr, materialPtr, aiTextureType_DIFFUSE, internal::Mesh::Texture::Type::Diffuse);
			 std::vector<internal::Mesh::Texture> specularTexs = loadMaterialTextures(_meshPtr, materialPtr, aiTextureType_SPECULAR, internal::Mesh::Texture::Type::Specular);

			 textures.insert(textures.end(), diffuseTexs.begin(), diffuseTexs.end());
			 textures.insert(textures.end(), specularTexs.begin(), specularTexs.end());
		 }

		 return internal::Mesh(vertices, indices, std::move(textures));
	 }

	 void Model::calcSize()
	 {
		 std::vector<float> xVec, yVec, zVec;

		 for(auto & mesh : m_meshes)
		 {
				std::pair<float, float> minMaxX, minMaxY, minMaxZ;
				std::tie(minMaxX, minMaxY, minMaxZ) = mesh.minMaxVerts;

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

	 void Model::setUp(const std::string & _path)
	 {
		  constexpr GLsizei stride = sizeof(internal::Mesh::Vertex);
#define offsetOfVertexMember(m) (GLvoid*)offsetof(internal::Mesh::Vertex, m)

		  loadModel(_path);
		  calcSize();
		  m_vaos.resize(m_meshes.size());

		  for (int i = 0; i < m_meshes.size(); i++)
		  {
				m_vaos[i].bind();

				m_meshes[i].vbo.bind();
				m_meshes[i].ebo.bind();

				glVertexAttribPointer(AttrLoc::Position, 3, GL_FLOAT, GL_FALSE, stride, offsetOfVertexMember(position));
				glEnableVertexAttribArray(AttrLoc::Position);

				glVertexAttribPointer(AttrLoc::Normal, 3, GL_FLOAT, GL_FALSE, stride, offsetOfVertexMember(normal));
				glEnableVertexAttribArray(AttrLoc::Normal);

				glVertexAttribPointer(AttrLoc::TexCoord, 2, GL_FLOAT, GL_FALSE, stride, offsetOfVertexMember(texCoords));
				glEnableVertexAttribArray(AttrLoc::TexCoord);

				m_vaos[i].unbind();
		  }
#undef offsetOfVertexMember
	 }

	 std::vector<internal::Mesh::Texture> Model::loadMaterialTextures(aiMesh * _mesh, aiMaterial * _materialPtr, aiTextureType _texType, internal::Mesh::Texture::Type _texTypeName)
	 {
		 std::vector<internal::Mesh::Texture> textures;

		 for(GLuint i = 0; i < _materialPtr->GetTextureCount(_texType); i++)
		 {
			 aiString str;
			 _materialPtr->GetTexture(_texType, i, &str);
			 GLboolean loaded = false;
			 for(internal::Mesh::Texture & tex : textures)
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
				 internal::Mesh::Texture texture;

				 std::string filePath = m_directory + '/' + str.C_Str();
				 std::string modelName = 'M' + std::to_string(s_createdNumber);

				 texture.id = 
					 fhl::ResMgr::loadTexture(modelName + "_" + std::to_string(m_meshCount++) + "_" +
						  internal::Mesh::Texture::typeToString(_texTypeName) + std::to_string(i), filePath).setRepeated(true).getId();
				 texture.type = _texTypeName;
				 texture.fileName = str;
				 textures.push_back(texture);
			 }
		 }
		 return textures;
	 }

} // ns
