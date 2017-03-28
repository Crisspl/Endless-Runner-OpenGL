#include "Configurator.h"

#include "../Utility/Debug.h"
#include "../Maths/mathsFuncs.h"

using namespace fhl::internal;

namespace fhl
{
	std::unique_ptr<internal::Buffer> Configurator::m_rectShapeEbo(nullptr);
	Mat4 Configurator::m_projection;
	Mat4 * Configurator::m_currentGlobal3DView{ nullptr };

	bool Configurator::m_initialized(false);
	const GLuint Configurator::m_rectShapeIndices[] =
	{
		 0, 1, 3,
		 1, 2, 3
	};
	Vec2i Configurator::m_vpSize;
	std::map<std::string, Mat4> Configurator::m_views;

	void Configurator::init(GLuint _width, GLuint _height)
	{
		if (m_initialized)
			return;

		glewExperimental = GL_TRUE;

		GLenum glewError = glewInit();

		if (glewError != GLEW_OK)
			fhl::DebugLog << "GLEW init error: " << glewGetErrorString(glewError) << '\n';

		glViewport(0, 0, _width, _height);
		m_vpSize = { static_cast<int>(_width), static_cast<int>(_height) };
		m_projection = Mat4::perspective(-45.f, -static_cast<float>(m_vpSize.x) / m_vpSize.y, 1e-1f, 1e4f);

		m_rectShapeEbo = std::make_unique<internal::Buffer>(Buffer::Target::ElementArrayBuffer, Buffer::Usage::StaticDraw);
		m_rectShapeEbo->bind();
		m_rectShapeEbo->setData(6 * sizeof(GLuint), m_rectShapeIndices);
		m_rectShapeEbo->unbind();

		setDefaultViewDistance(726.f);
		m_currentGlobal3DView = &m_views[m_defViewName];

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_initialized = true;
	}

	Mat4 Configurator::getView(const std::string & _name)
	{
		if (m_views.find(_name) != m_views.end())
			return m_views[_name];
		else
			return Mat4::identity();
	}

	void Configurator::setDefaultViewDistance(float _eyeZ)
	{
		Vec2f halfVp = Vec2f(m_vpSize) / 2.f;
		std::cout << halfVp;
		m_views[m_defViewName] = Mat4::lookAt(Vec3f(halfVp.x, halfVp.y, _eyeZ), Vec3f(halfVp.x, halfVp.y, 0), Vec3f::up());
	}

	void Configurator::setGlobal3DView(const std::string & _name)
	{
		if (m_views.find(_name) != m_views.end())
			m_currentGlobal3DView = &m_views[_name];
	}

	void Configurator::setView(const std::string & _name, const Mat4 & _view)
	{
		if (m_views.find(_name) == m_views.end())
			m_views[_name] = _view;
	}

	void Configurator::addView(const std::string & _name, const Mat4 & _view)
	{
		if (m_views.find(_name) != m_views.end())
			m_views[_name] = _view;
	}

} // ns
