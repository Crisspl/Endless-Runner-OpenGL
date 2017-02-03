#ifndef ANIMATIONMGR_H
#define ANIMATIONMGR_H

#include "Utility/Rect.h"
#include "Graphics/Sprite.h"
#include "Maths/vectors.h"

class AnimationMgr
{
public:
   AnimationMgr(fhl::Sprite* _sprt, float _interval, fhl::Vec2f _fSize);

public:
   void update(float _dt);

   AnimationMgr& setRow(std::size_t _r) { m_currentRow = _r; return *this; }
   AnimationMgr& setFrameSize(fhl::Vec2f _size) { m_frameSize = _size; return *this; }

private:
   fhl::Sprite* m_ptrSprite;
   float m_currentFrameTime;
   std::size_t m_currentRow;
   std::size_t m_frameCounter;
   float m_interval;
   fhl::Vec2f m_frameSize;
};

#endif // ANIMATIONMGR_H
