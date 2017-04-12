#include "Texture.h"

#include <algorithm>

namespace fhl
{

	 Texture::Texture(Vec2i _size)
				 : m_size(_size),
					m_repeated(false)
	 {
		 glGenTextures(1, &m_id);
		 glBindTexture(GL_TEXTURE_2D, m_id);

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
		 uchar * tmp;
		 std::tie(tmp, m_size, m_id) = loadImage(_filePath);

		 glBindTexture(GL_TEXTURE_2D, m_id);
		 glGenerateMipmap(GL_TEXTURE_2D);

		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		 setRepeated(false);
	 }

	 Texture::Texture(Texture && _other) 
			 : m_id(_other.m_id),
				m_size(_other.m_size),
				m_repeated(_other.m_repeated)
	 {
		 _other.m_id = 0;
	 }

	 Texture & Texture::operator=(Texture && _other)
	 {
		  std::swap(m_id, _other.m_id);
		  m_size = _other.m_size;
		  m_repeated = _other.m_repeated;

		  return *this;
	 }


	 Texture::~Texture()
	 {
		 glDeleteTextures(1, &m_id);
	 }

	 const Texture& Texture::setWrapOption(Texture::WrapOption _option) const
	 {
		 glBindTexture(GL_TEXTURE_2D, m_id);

		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _option);
		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _option);

		 glBindTexture(GL_TEXTURE_2D, 0);

		 return *this;
	 }

	 std::tuple<unsigned char*, Vec2i, GLuint> Texture::loadImage(std::string _filePath)
	 {
		 GLuint id;
		 Vec2i size;
		 uchar * image = SOIL_load_image(_filePath.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);

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
