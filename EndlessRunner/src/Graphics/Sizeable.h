#ifndef SIZEABLE_H
#define SIZEABLE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <memory>

#include "Buffer.h"
#include "Vao.h"

namespace gr
{

class Sizeable
{
public:
   explicit Sizeable(glm::vec2 _size = {1, 1});
   virtual ~Sizeable() { }

   virtual void setSize(glm::vec2 _size);
   glm::vec2 getSize() const { return m_size; }

protected:
   void updatePosArray();
   void uploadPosArray();

protected:
   std::shared_ptr<Vao> m_vao;

   glm::vec2 m_size;
   glm::vec2 m_posArray[4];
};

} // ns

#endif // SIZEABLE_H
