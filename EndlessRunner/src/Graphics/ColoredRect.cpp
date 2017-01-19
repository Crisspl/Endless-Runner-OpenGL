#include "ColoredRect.h"
#include "Configurator.h"

namespace fhl
{

	 ColoredRect::ColoredRect(Vec2f _size)
		  : Sizeable(_size),
		  UsingShader(&ResMgr::getLoadShader(SHADER_NAME, shaderSrcs::coloredRect_Vertex, shaderSrcs::coloredRect_Fragment, Shader::FromString),
						  &ResMgr::getLoadShader(LIGHT_SHADER_NAME, shaderSrcs::coloredRect_LightVertex, shaderSrcs::coloredRect_LightFragment, Shader::FromString)),
		  m_color(Color::Transparent),
		  m_usingOriginalShader(true)
	 {
		  setUp();
	 }

	 void ColoredRect::render(const RenderConf & _conf) const
	 {
		  m_shader->use();
	 
		  bool useCustomConf = _conf != RenderConf::Default;

		  m_shader->setMat4("mvp", useCustomConf ? _conf.matrices.mvp : getMVP())
				.setMat4("transform", useCustomConf ? _conf.matrices.transform : getTransform())
				.setVec4f("vertColor", m_color.asVec4())
				.setLights("light", getLights().cbegin(), getLights().cend());

		  m_vao->bind();
		  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  m_vao->unbind();

		  Shader::unUse();
	 }

	 void ColoredRect::setUp()
	 {
		  m_vao->bind();

		  Configurator::rectShapeEbo->bind();

		  m_vao->unbind();
	 }

}