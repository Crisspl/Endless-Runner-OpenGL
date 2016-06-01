#include "Vao.h"

namespace gr
{

Vao::Vao()
{
   glGenVertexArrays(1, &id);
}

Vao::Vao(Vao&& _src)
   : id(_src.id),
     m_buffers(std::move(_src.m_buffers))
{
   for(auto& el : _src.m_buffers)
      el.second = nullptr;
}

Vao::~Vao()
{
   for(auto& pBuffer : m_buffers)
      delete pBuffer.second;
   glDeleteVertexArrays(1, &id);
}

void Vao::bind() const
{
   glBindVertexArray(id);
}

void Vao::unbind() const
{
   glBindVertexArray(0);
}

Buffer* Vao::getBuffer(std::string _key)
{
   return m_buffers[_key];
}

void Vao::addBuffer(std::string _key, Buffer* _buffer)
{
   m_buffers[_key] = _buffer;
}

}
