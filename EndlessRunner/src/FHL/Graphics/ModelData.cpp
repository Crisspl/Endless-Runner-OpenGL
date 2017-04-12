#include <FHL/Graphics/ModelData.h>

#include <FHL/Graphics/ResMgr.h>

namespace fhl
{
	std::size_t ModelData::s_createdCount = 0;

	ModelData::ModelData(const std::string & _path) :
		m_directory{ _path.substr(0, _path.find_last_of('/')) },
		m_meshCount{ 0 }
	{
		load(_path);
		calcSize();
		++s_createdCount;
	}

	ModelData::~ModelData()
	{
		for (const std::string & name : m_texNames)
			ResMgr::removeTexture(name);
	}

	void ModelData::load(const std::string & _path)
	{
		Assimp::Importer importer;
		const aiScene * const scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			fhl::DebugLog << "Error loading model: " << importer.GetErrorString() << '\n';
			return;
		}
		processNode(scene->mRootNode, scene);
	}

	void ModelData::processNode(aiNode * _nodePtr, const aiScene * _scenePtr)
	{
		for (GLuint i = 0; i < _nodePtr->mNumMeshes; i++)
		{
			aiMesh * meshPtr = _scenePtr->mMeshes[_nodePtr->mMeshes[i]];
			m_meshes.push_back(processMesh(meshPtr, _scenePtr));
		}

		for (GLuint i = 0; i < _nodePtr->mNumChildren; i++)
			processNode(_nodePtr->mChildren[i], _scenePtr);
	}

	internal::Mesh ModelData::processMesh(aiMesh * _meshPtr, const aiScene * _scenePtr)
	{
		std::vector<internal::Mesh::Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<internal::Mesh::Texture> textures;

		vertices.reserve(_meshPtr->mNumVertices);
		for (GLuint i = 0; i < _meshPtr->mNumVertices; i++)
		{
			internal::Mesh::Vertex vertex;
			vertex.position = { _meshPtr->mVertices[i].x, _meshPtr->mVertices[i].y, _meshPtr->mVertices[i].z };
			vertex.normal = { _meshPtr->mNormals[i].x, _meshPtr->mNormals[i].y, _meshPtr->mNormals[i].z };

			if (_meshPtr->mTextureCoords[0])
				vertex.texCoords = { _meshPtr->mTextureCoords[0][i].x, _meshPtr->mTextureCoords[0][i].y };
			else
				vertex.texCoords = Vec2f::zero();

			vertices.push_back(vertex);
		}

		for (GLuint i = 0; i < _meshPtr->mNumFaces; i++)
		{
			const aiFace & face = _meshPtr->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (_meshPtr->mMaterialIndex >= 0)
		{
			aiMaterial* materialPtr = _scenePtr->mMaterials[_meshPtr->mMaterialIndex];

			std::vector<internal::Mesh::Texture> diffuseTexs = loadMaterialTextures(_meshPtr, materialPtr, aiTextureType_DIFFUSE, internal::Mesh::Texture::Type::Diffuse);
			std::vector<internal::Mesh::Texture> specularTexs = loadMaterialTextures(_meshPtr, materialPtr, aiTextureType_SPECULAR, internal::Mesh::Texture::Type::Specular);

			textures.insert(textures.end(), diffuseTexs.begin(), diffuseTexs.end());
			textures.insert(textures.end(), specularTexs.begin(), specularTexs.end());
		}

		return internal::Mesh(vertices, indices, std::move(textures));
	}

	void ModelData::calcSize()
	{
		std::vector<float> xVec, yVec, zVec;

		for (auto & mesh : m_meshes)
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

	std::vector<internal::Mesh::Texture> ModelData::loadMaterialTextures(aiMesh * _mesh, aiMaterial * _materialPtr, aiTextureType _texType, internal::Mesh::Texture::Type _texTypeName)
	{
		std::vector<internal::Mesh::Texture> textures;

		for (GLuint i = 0; i < _materialPtr->GetTextureCount(_texType); i++)
		{
			aiString str;
			_materialPtr->GetTexture(_texType, i, &str);
			GLboolean loaded = false;
			for (internal::Mesh::Texture & tex : textures)
			{
				if (tex.fileName == str)
				{
					textures.push_back(tex);
					loaded = true;
					break;
				}
			}

			if (!loaded)
			{
				internal::Mesh::Texture texture;

				std::string filePath = m_directory + '/' + str.C_Str();
				std::string modelName = "_FHL_M" + std::to_string(s_createdCount);
				std::string texName = modelName + '_' + std::to_string(m_meshCount++) + '_' +
					internal::Mesh::Texture::typeToString(_texTypeName) + std::to_string(i);

				texture.id = fhl::ResMgr::loadTexture(texName, filePath).setRepeated(true).getId();
				texture.type = _texTypeName;
				texture.fileName = str;
				textures.push_back(texture);
				m_texNames.push_back(std::move(texName));
			}
		}
		return textures;
	}

} // ns
