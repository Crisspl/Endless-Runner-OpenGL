#ifndef FHL_TEXTURE_H
#define FHL_TEXTURE_H

#include <SOIL/SOIL.h>

#include <string>
#include <vector>
#include <tuple>

#include <FHL/GL/gl3w.h>
#include <FHL/Maths/vectors.h>

namespace fhl { class ResMgr; }

namespace fhl
{

	 class Texture
	 {

		  friend class fhl::ResMgr;

		  template<typename, typename>
		  friend struct std::pair;

	 private:
		  using uchar = unsigned char;

	 private:
		  enum WrapOption
		  {
				Repeat = GL_REPEAT,
				ClampToBorder = GL_CLAMP_TO_BORDER
		  };

	 private:
		  Texture(const Texture &) = delete;
		  Texture & operator=(const Texture &) = delete;
		  Texture(Texture && _other);
		  Texture & operator=(Texture && _other);
		  explicit Texture(Vec2i _size);
		  explicit Texture(std::string _filePath);
		  ~Texture();

		  const Texture & setWrapOption(WrapOption _option) const;

		  std::tuple<uchar *, Vec2i, GLuint> loadImage(std::string _filePath);

	 public:
		  GLuint getId() const { return m_id; }
		  Vec2i getSize() const { return m_size; }

		  Texture & setRepeated(bool _r);
		  bool isRepeated() const { return m_repeated; }

	 private:
		  GLuint m_id;
		  Vec2i m_size;
		  bool m_repeated;
	 };

} // ns

#endif // FHL_TEXTURE_H

