#include "Vao.h"

namespace fhl
{

	 Vao::Vao()
	 {
		 glGenVertexArrays(1, &id);
	 }

	 Vao::Vao(Vao && _other)
		 : id(_other.id),
		 m_buffers(std::move(_other.m_buffers))
	 {
		 for (auto& el : _other.m_buffers)
			 el.second = nullptr;
		 _other.id = 0;
	 }

	 Vao::~Vao()
	 {
		 for (auto& pBuffer : m_buffers)
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
