#include "Texture.h"

namespace fhl
{

Texture::Texture(vec2i _size)
         : m_size(_size),
           m_repeated(false)
{
   glGenTextures(1, &m_texId);
   glBindTexture(GL_TEXTURE_2D, m_texId);

   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

   glBindTexture(GL_TEXTURE_2D, 0);

   setRepeated(false);
}

Texture::Texture(std::string _filePath)
{
   uchar* tmp;
   std::tie(tmp, m_size, m_texId) = loadImage(_filePath);

   glBindTexture(GL_TEXTURE_2D, m_texId);
   glGenerateMipmap(GL_TEXTURE_2D);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   setRepeated(false);
}

const Texture& Texture::setWrapOption(Texture::WrapOption _option) const
{
   glBindTexture(GL_TEXTURE_2D, m_texId);

   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _option);
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _option);

   glBindTexture(GL_TEXTURE_2D, 0);

   return *this;
}

std::tuple<unsigned char*, glm::vec2, GLuint> Texture::loadImage(std::string _filePath)
{
   GLuint id;
   vec2i size;
   unsigned char* image = SOIL_load_image(_filePath.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
   std::cout << "load tex: " << _filePath << std::endl;
   std::cout << size.x << ' ' << size.y <<std::endl;

   glGenTextures(1, &id);
   glBindTexture(GL_TEXTURE_2D, id);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
   SOIL_free_image_data(image);
   glBindTexture(GL_TEXTURE_2D, 0);

   return std::make_tuple(image, size, id);
}

Texture& Texture::setRepeated(bool _r)
{
   if(_r)
      setWrapOption(Repeat);
   else
      setWrapOption(ClampToBorder);
   m_repeated = _r;
   return *this;
 }

} // ns
