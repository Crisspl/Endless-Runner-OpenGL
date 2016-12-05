#ifndef VAO_H
#define VAO_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <map>
#include <string>
#include <utility>

#include "Buffer.h"

namespace fhl
{

class Vao
{
public:
	Vao();
	Vao(const Vao&) = delete;
	Vao(Vao &&);
	~Vao();

	void bind() const;
	void unbind() const;

	Buffer* getBuffer(std::string _key);
	void addBuffer(std::string _key, Buffer* _buffer);

public:
	GLuint id;

private:
	std::map<std::string, Buffer*> m_buffers;
};

}

#endif // VAO_H