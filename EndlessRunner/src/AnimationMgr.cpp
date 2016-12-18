#include "AnimationMgr.h"

AnimationMgr::AnimationMgr(fhl::Sprite* _sprt, float _interval, fhl::Vec2f _fSize)
   : m_ptrSprite(_sprt),
     m_interval(_interval),
     m_frameSize(_fSize)
{

}

void AnimationMgr::update(float _dt)
{
   if(!m_ptrSprite->getTexture())
      return;

   m_currentFrameTime += _dt;
   if(m_currentFrameTime >= m_interval)
   {
      m_currentFrameTime = 0;
      m_ptrSprite->setTextureRect(fhl::Rect({m_frameCounter * m_frameSize.x, m_currentRow * m_frameSize.y}, m_frameSize));
      if(++m_frameCounter == m_ptrSprite->getTexture()->getSize().x / m_frameSize.x)
         m_frameCounter = 0;
   }
}
