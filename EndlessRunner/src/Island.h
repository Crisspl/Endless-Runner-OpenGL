#ifndef ISLAND_H
#define ISLAND_H

#include <vector>
#include <random>

#include "Global.h"
#include "Graphics/ResMgr.h"
#include "Collideable.h"
#include "Graphics/Sprite.h"
#include "Graphics/Drawable.h"
#include "Graphics/DrawFuncs.h"
#include "Graphics/Light.h"
#include "Coin.h"

class Island
      : public Collideable,
        public fhl::Drawable
{
public:
   explicit Island(glm::vec2 _pos);
   ~Island();
public:
   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void update(float _dt);
   void draw(const fhl::DrawConf &) const override;
   void move(float _offset);

   glm::vec2 getPosition() const { return m_sprite.getPosition(); }
   float getSurfaceHeight() const { return m_sprite.getPosition().y; }
   std::vector<fhl::Light> getLights() const;
   std::vector<Coin> & getCoins() { return m_coins; }

private:
   fhl::Sprite m_sprite;
   std::vector<Coin> m_coins;
};

#endif // ISLAND_H
