#pragma once

#include <vector>
#include <random>

#include "Global.h"
#include "Utility/ResMgr.h"
#include "Collideable.h"
#include "Graphics/Sprite.h"
#include "Graphics/Drawable.h"

class Island
      : public Collideable,
        public gr::Drawable
{
public:
   explicit Island(glm::vec2 _pos);
   ~Island();
public:
   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void draw() const override;
   void move(float _offset);

   glm::vec2 getPosition() const { return m_vecElements.rbegin()->getPosition(); }
   float getSurfaceHeight() const;

private:
   std::vector<gr::Sprite> m_vecElements;
};
