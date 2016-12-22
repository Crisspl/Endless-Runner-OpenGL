#ifndef FHL_TEXTUREDSIZEABLE_H
#define FHL_TEXTUREDSIZEABLE_H

#include "Sizeable.h"
#include "Texture.h"

namespace fhl
{

class TexturedSizeable
	: public Sizeable
{
public:
	explicit TexturedSizeable(Texture* _tex, Vec2f _size = { 0, 0 });

	void setSize(Vec2f _size) override;
	void uploadTexCoordsArray();

protected:
	Texture* m_ptexture;
	Vec2f m_texCoordsArray[4];

private:
	void fillTxcArray(Vec2f _v);
};

} // ns


#endif // FHL_TEXTUREDSIZEABLE_H
