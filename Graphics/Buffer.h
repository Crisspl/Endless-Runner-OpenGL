#ifndef BUFFER_H
#define BUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

namespace gr
{

struct Buffer
{
   Buffer(GLuint _target, GLuint _usage);
   Buffer(const Buffer&) = delete;
   ~Buffer();

   void bind();
   void unbind();
   void setData(GLuint _size, const void* _data);
   void updateData(GLuint _offset, GLuint _size, const void* _data);

private:
   GLuint id;

public:
   GLuint target, usage;
   GLuint size;
};

}

#endif // BUFFER_H
