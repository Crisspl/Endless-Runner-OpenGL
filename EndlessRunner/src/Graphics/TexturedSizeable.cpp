#include "TexturedSizeable.h"

namespace fhl
{

TexturedSizeable::TexturedSizeable(Texture* _tex, glm::vec2 _size)
   : Sizeable(_size),
     m_ptexture(_tex),
     m_texCoordsArray{ {0, 0}, {1, 0}, {1, 1}, {0, 1} }
{
   Buffer* texCoordsBuffer = new Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
   m_vao->addBuffer("texCoordsBuffer", texCoordsBuffer);

   m_vao->bind();

   texCoordsBuffer->bind();
   texCoordsBuffer->setData(sizeof(m_texCoordsArray), m_texCoordsArray);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
   glEnableVertexAttribArray(1);

   m_vao->unbind();
}

void TexturedSizeable::setSize(glm::vec2 _size)
{
   if(!m_ptexture)
      return;

   Sizeable::setSize(_size);

   glm::vec2 h = m_size / m_ptexture->getSize();
   if(m_ptexture->isRepeated())
      fillTxcArray(h);
   else
      fillTxcArray({1 ,1});

   uploadTexCoordsArray();
}

void TexturedSizeable::uploadTexCoordsArray()
{
   Buffer* txcBuffer = m_vao->getBuffer("texCoordsBuffer");
   txcBuffer->bind();
   txcBuffer->updateData(0, sizeof(m_texCoordsArray), m_texCoordsArray);
   txcBuffer->unbind();
}

void TexturedSizeable::fillTxcArray(glm::vec2 _v)
{
   m_texCoordsArray[0] = {0, 0};
   m_texCoordsArray[1] = {_v.x, 0};
   m_texCoordsArray[2] = _v;
   m_texCoordsArray[3] = {0, _v.y};
}

} // ns
