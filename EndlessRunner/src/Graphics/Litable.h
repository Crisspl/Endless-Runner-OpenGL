#ifndef FHL_LITABLE_H
#define FHL_LITABLE_H

#include "Light.h"

#include <list>
#include <vector>

namespace fhl
{

	 class Litable
	 {
	 public:
		  virtual ~Litable() = default;

		  void addLight(const Light & _light)
		  {
				m_lights.push_back(_light);
		  }
		  void addLights(const std::vector<Light> & _lights)
		  {
				m_lights.insert(m_lights.cbegin(), _lights.cbegin(), _lights.cend());
		  }

		  void setLight(const Light & _light)
		  {
				m_lights.clear();
				addLight(_light);
		  }
		  void setLights(const std::vector<Light> & _lights)
		  {
				m_lights.clear();
				addLights(_lights);
		  }

		  size_t getLightsCount() const { return m_lights.size(); }
		  const std::list<Light> & getLights() const { return m_lights; }

	 protected:
		  std::list<Light> m_lights;
	 };

}

#endif // FHL_LITABLE_H
