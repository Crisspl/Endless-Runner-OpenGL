#include "Buffer.h"

namespace gr
{

Buffer::Buffer(GLuint _target, GLuint _usage)
   : target(_target),
     usage(_usage),
     size(0)
{
   glGenBuffers(1, &id);
}

Buffer::~Buffer()
{
   glDeleteBuffers(1, &id);
}

void Buffer::bind()
{
   glBindBuffer(target, id);
}

void Buffer::unbind()
{
   glBindBuffer(target, 0);
}

void Buffer::setData(GLuint _size, const void* _data)
{
   size = _size;
   glBufferData(target, _size, _data, usage);
}

void Buffer::updateData(GLuint _offset, GLuint _size, const void* _data)
{
   //assert(_offset + _size <= size);
   glBufferSubData(target, _offset, _size, _data);
}

}
