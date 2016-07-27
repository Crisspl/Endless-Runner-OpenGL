#ifndef ANIMATIONMGR_H
#define ANIMATIONMGR_H

#include <glm/glm.hpp>

#include "Utility/Rect.h"
#include "Graphics/Sprite.h"

class AnimationMgr
{
public:
   AnimationMgr(gr::Sprite* _sprt, float _interval, glm::vec2 _fSize);

public:
   void update(float _dt);

   AnimationMgr& setRow(std::size_t _r) { m_currentRow = _r; return *this; }
   AnimationMgr& setFrameSize(glm::vec2 _size) { m_frameSize = _size; return *this; }

private:
   gr::Sprite* m_ptrSprite;
   float m_currentFrameTime;
   std::size_t m_currentRow;
   std::size_t m_frameCounter;
   float m_interval;
   glm::vec2 m_frameSize;
};

#endif // ANIMATIONMGR_H
