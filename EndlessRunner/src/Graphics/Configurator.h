#ifndef FHL_CONFIGURATOR_H
#define FHL_CONFIGURATOR_H

#include <GL/glew.h>

#include <memory>
#include <map>

#include "Buffer.h"
#include "../Maths/vectors.h"
#include "../Maths/Mat4.h"

namespace fhl
{

	class Configurator
	{
		Configurator() = delete;

	public:
		static void init(GLuint _width, GLuint _height);

		static Vec2i viewportSize() { return m_vpSize; }
		static const Mat4 & view() { return m_views[m_defViewName]; }
		static const Mat4 & global3DView() { return *m_currentGlobal3DView; }
		static Mat4 getView(const std::string & _name);
		static const Mat4 & projection() { return m_projection; }

		static void setDefaultViewDistance(float _eyeZ);
		static void setGlobal3DView(const std::string & _name);
		static void setView(const std::string & _name, const Mat4 & _view);
		static void addView(const std::string & _name, const Mat4 & _view);
		static void resetGlobal3DView() { m_currentGlobal3DView = &m_views[m_defViewName]; }

	public:
		static std::unique_ptr<internal::Buffer> rectShapeEbo;

	private:
		static Mat4 m_projection;
		static Mat4 * m_currentGlobal3DView;
		static bool m_initialized;
		static const GLuint m_rectShapeIndices[6];
		static Vec2i m_vpSize;
		static std::map<std::string, Mat4> m_views;

		static constexpr const char * m_defViewName = "_FHL_default";
	};

} // ns

#endif // FHL_CONFIGURATOR_H
