#ifndef FHL_CONFIGURATOR_H
#define FHL_CONFIGURATOR_H

#include <GL/glew.h>

#include <memory>
#include <map>

#include "Buffer.h"
#include "View.h"

namespace fhl
{

	class Configurator
	{
		Configurator() = delete;

	public:
		static void init(GLuint _width, GLuint _height);

		static Vec2i viewportSize() { return m_vpSize; }
		static const Mat4 & view() { return m_views[m_defViewName].matrix; }
		static const Vec3f & cameraPos() { return m_views[m_defViewName].cameraPos; }
		static const View & global3DView() { return *m_currentGlobal3DView; }
		static View getView(const std::string & _name);
		static const Mat4 & projection() { return m_projection; }
		constexpr static const char * getDefaultViewName() { return m_defViewName; }

		static void setDefaultViewDistance(float _eyeZ);
		static void setGlobal3DView(const std::string & _name);
		static void setView(const std::string & _name, const Vec3f & _eye, const Vec3f & _center, const Vec3f & _up);
		static void addView(const std::string & _name, const Vec3f & _eye, const Vec3f & _center, const Vec3f & _up);
		static void resetGlobal3DView() { m_currentGlobal3DView = &m_views[m_defViewName]; }

		static void setEnableDepthTest(bool _enable);
		static bool isDepthTestEnabled() { return m_depthTestEnabled; }

		static const internal::Buffer & getRectShapeEbo() { return *m_rectShapeEbo; }

	private:
		static bool m_initialized;
		static std::unique_ptr<internal::Buffer> m_rectShapeEbo;
		static Mat4 m_projection;
		static View * m_currentGlobal3DView;
		static const GLuint m_rectShapeIndices[6];
		static Vec2i m_vpSize;
		static std::map<std::string, View> m_views;
		static bool m_depthTestEnabled;

		static constexpr const char * m_defViewName = "_FHL_default";
	};

} // ns

#endif // FHL_CONFIGURATOR_H
