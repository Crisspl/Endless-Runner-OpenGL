#ifndef FHL_BUFFER_H
#define FHL_BUFFER_H

#include <GL/glew.h>

#include <iostream>

namespace fhl
{

	 struct Buffer
	 {
		 Buffer(GLuint _target, GLuint _usage);
		 Buffer(const Buffer &) = delete;
		 Buffer(Buffer && _other);
		 ~Buffer();

		 void bind();
		 void unbind();
		 void setData(GLuint _size, const void* _data);
		 void updateData(GLuint _offset, GLuint _size, const void* _data);

	 private:
		 GLuint m_id;

	 public:
		 GLuint target, usage;
		 GLuint size;
	 };

}

#endif // FHL_BUFFER_H
