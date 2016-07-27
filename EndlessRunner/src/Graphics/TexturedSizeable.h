#ifndef TEXTUREDSIZEABLE_H
#define TEXTUREDSIZEABLE_H

#include "Sizeable.h"
#include "Texture.h"

namespace gr
{

class TexturedSizeable
   : public Sizeable
{
public:
   explicit TexturedSizeable(Texture* _tex, glm::vec2 _size = {0, 0});

   void setSize(glm::vec2 _size) override;
   void uploadTexCoordsArray();

protected:
   Texture* m_ptexture;
   glm::vec2 m_texCoordsArray[4];

private:
   void fillTxcArray(glm::vec2 _v);
};

} // ns


#endif // TEXTUREDSIZEABLE_H
