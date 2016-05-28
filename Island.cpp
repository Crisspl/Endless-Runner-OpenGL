#include "Island.h"

Island::Island(glm::vec2 _pos)
          : Collideable(Collideable::Coll_Island)
{
   m_vecElements = std::vector<gr::Sprite>(sup::getRand(7, 14), gr::Sprite(ut::ResMgr::getTexture("islandTex")));
   for(short i = 0; i < m_vecElements.size(); i++)
   {
      m_vecElements[i].setOrigin({32.f, 0.f})
            .setPosition({_pos.x + i * (m_vecElements[0].getSize().x ), _pos.y});
   }
}

Island::~Island()
{
}

std::shared_ptr<Collider> Island::getCollider(CollideableObjType _objType)
{
/*
   std::vector<ut::Rect> rects;

   for(auto& el : m_vecElements)
      rects.push_back(el.getRect());

   return std::shared_ptr<Collider>(new RectsCollider(rects));
*/
   ut::OrientedRect rect = m_vecElements[0].getOBB();

   rect.addWidth(m_vecElements.size() * 32 - 32);
   //rect.applyTransformData(m_vecElements[0].getTransformData());

   return std::shared_ptr<Collider>(new BoxCollider(rect));
}

void Island::draw() const
{
   for(const gr::Sprite& el : m_vecElements)
      el.draw();
}

void Island::move(float _offset)
{
   for(gr::Sprite& el : m_vecElements)
      el.move({_offset, 0});
}

float Island::getSurfaceHeight() const
{
   return m_vecElements[0].getPosition().y;
}
