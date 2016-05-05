#include "Sizeable.h"

namespace gr
{

Sizeable::Sizeable(glm::vec2 _size)
   : m_size(_size),
     m_posBuffer(new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW))
{
   updatePosArray();

   m_posBuffer->bind();
   m_posBuffer->setData(sizeof(m_posArray), m_posArray);
   m_posBuffer->unbind();
}

void Sizeable::setSize(glm::vec2 _size)
{
   m_size = _size;

   updatePosArray();
   uploadPosArray();
}

void Sizeable::updatePosArray()
{
   m_posArray[0] = glm::vec2(0.f, 0.f);
   m_posArray[1] = glm::vec2(m_size.x, 0.f);
   m_posArray[2] = glm::vec2(m_size.x, m_size.y);
   m_posArray[3] = glm::vec2(0.f, m_size.y);
}

void Sizeable::uploadPosArray()
{
   m_posBuffer->bind();
   m_posBuffer->updateData(0, sizeof(m_posArray), m_posArray);
   m_posBuffer->unbind();
}

} // ns
