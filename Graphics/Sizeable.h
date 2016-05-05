#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Buffer.h"

namespace gr
{

class Sizeable
{
public:
   explicit Sizeable(glm::vec2 _size = {1, 1});

   void setSize(glm::vec2 _size);
   glm::vec2 getSize() const { return m_size; }

protected:
   void updatePosArray();
   void uploadPosArray();

protected:
   glm::vec2 m_size;
   Buffer* m_posBuffer;
   glm::vec2 m_posArray[4];
};

} // ns
