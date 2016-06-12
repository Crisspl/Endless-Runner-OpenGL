#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <tuple>
#include <iostream>

namespace ut { class ResMgr; }

namespace gr
{

class Texture
{

   friend class ut::ResMgr;

   template<class A, class B>
      friend struct std::pair;

private:
   typedef unsigned char uchar;
   typedef glm::tvec2<GLint> vec2i;

private:
   enum WrapOption
   {
      Repeat = GL_REPEAT,
      ClampToBorder = GL_CLAMP_TO_BORDER
   };

private:
   Texture() = default;
   explicit Texture(vec2i _size);
   explicit Texture(std::string _filePath);

   const Texture& setWrapOption(WrapOption _option) const;

   std::tuple<uchar*, glm::vec2, GLuint> loadImage(std::string _filePath);

public:
   const GLuint& getId() const { return m_texId; }
   glm::vec2 getSize() const { return glm::vec2(m_size.x, m_size.y); }

   Texture& setRepeated(bool _r);
   bool isRepeated() { return m_repeated; }

private:
   GLuint m_texId;
   vec2i m_size;
   uchar* m_imageData;
   bool m_repeated;
};

} // ns

