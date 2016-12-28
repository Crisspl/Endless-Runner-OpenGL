#ifndef FHL_SIZEABLE_H
#define FHL_SIZEABLE_H

#include <GL/glew.h>

#include <memory>

#include "Buffer.h"
#include "Vao.h"
#include "../Maths/Vectors.h"

namespace fhl
{

	 class Sizeable
	 {
	 public:
		 explicit Sizeable(Vec2f _size = { 1, 1 });
		 virtual ~Sizeable() { }

		 virtual void setSize(Vec2f _size);
		 Vec2f getSize() const { return m_size; }

	 protected:
		 void updatePosArray();
		 void uploadPosArray();

	 protected:
		 std::shared_ptr<Vao> m_vao;

		 Vec2f m_size;
		 Vec2f m_posArray[4];
	 };

} // ns

#endif // FHL_SIZEABLE_H
