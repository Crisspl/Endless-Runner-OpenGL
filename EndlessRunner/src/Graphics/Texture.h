#ifndef FHL_TEXTURE_H
#define FHL_TEXTURE_H

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <tuple>

#include "../Maths/Vectors.h"

namespace fhl { class ResMgr; }

namespace fhl
{

	 class Texture
	 {

	 friend class fhl::ResMgr;

	 template<typename, typename>
		 friend struct std::pair;

	 private:
		 typedef unsigned char uchar;
	 private:
		 enum WrapOption
		 {
			 Repeat = GL_REPEAT,
			 ClampToBorder = GL_CLAMP_TO_BORDER
		 };

	 private:
		 Texture() = delete;
		 Texture(const Texture &) = delete;
		 Texture(Texture && _other);
		 explicit Texture(Vec2i _size);
		 explicit Texture(std::string _filePath);

		 ~Texture();

		 const Texture& setWrapOption(WrapOption _option) const;

		 std::tuple<uchar*, Vec2i, GLuint> loadImage(std::string _filePath);

	 public:
		 GLuint getId() const { return m_texId; }
		 Vec2i getSize() const { return m_size; }

		 Texture & setRepeated(bool _r);
		 bool isRepeated() { return m_repeated; }

	 private:
		 GLuint m_texId;
		 Vec2i m_size;
		 bool m_repeated;
	 };

} // ns

#endif // FHL_TEXTURE_H

