#ifndef FHL_MODEL_H
#define FHL_MODEL_H

#include "Vao.h"
#include "Renderable.h"
#include "Transformable3D.h"
#include "Litable.h"
#include "UsingShader.h"
#include "ModelData.h"

namespace fhl
{
	class ResMgr;
	class ModelData;

	class Model :
		public Renderable,
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
		explicit Model(ModelData & _data);
		Model(Model &&) = default;
		Model & operator=(Model &&) = default;

		void render(const RenderConf & _conf) const override;
		void setModelData(ModelData & _data);

		Vec3f getSize() const { return m_modelData->getSize(); }
		const ModelData * getModelData() const { return m_modelData; }

	private:
		void setUp();
		void renderMeshes() const;

	private:
		ModelData * m_modelData;
		std::vector<internal::Vao> m_vaos;

		constexpr static const char * simpleShaderName = "_FHL_modelSimpleShader";
		constexpr static const char * lightShaderName = "_FHL_modelLightShader";
	};

} // ns

#endif // FHL_MODEL_H
