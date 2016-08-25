#include "Island.h"

Island::Island(glm::vec2 _pos)
          : Collideable(Collideable::Coll_Island)
{
   m_sprite.setTexture(fhl::ResMgr::getTexture("islandTex"));
   fhl::ResMgr::getTexture("islandTex").setRepeated(true);

   std::size_t size = sup::getRand(7, 14);

   m_sprite.setSize({ size * 32, 32 });
   m_sprite.setOrigin({32.f * size , 0.f})
           .setPosition(_pos);
}

Island::~Island()
{
}

std::shared_ptr<Collider> Island::getCollider(CollideableObjType _objType)
{
   fhl::Rect *rect = new fhl::Rect(m_sprite.getAABB());

   return std::shared_ptr<Collider>(new BoxCollider(rect));
}

void Island::draw(const fhl::DrawConf &) const
{
	fhl::draw(m_sprite);
}


void Island::move(float _offset)
{
   m_sprite.move({_offset, 0});
}
