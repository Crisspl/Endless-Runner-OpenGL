#ifndef HERO_H
#define HERO_H

#include "Graphics/Sprite.h"
#include "Collideable.h"
#include "Graphics/Drawable.h"
#include "Global.h"
#include "AnimationMgr.h"

#define DECLARE_HERO_STATE_METHODS(stateName) \
   void stateName##_onEnter(const Hero::State); \
   void stateName##_onExit(const Hero::State); \
   void stateName##_update(float);

class Hero
      : public Collideable,
        public gr::Drawable
{
public:
   enum State
   {
     State_Move,
     State_Jump,
     State_Fall,

     StateCount
   };

public:
   Hero();
   ~Hero() {}

   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void draw() const override;
   void update(float dt);
   void changeState(const State _newState);

   glm::vec2 getPosition() const { return m_heroSprite.getPosition(); }
   State getState() const { return m_currentState; }

   void setPosition(glm::vec2 _pos) { m_heroSprite.setPosition(_pos); }
   void setPosY(float _y) { m_heroSprite.setPosition({getPosition().x, _y}); }

private:
   void move(glm::vec2 _offset);

   DECLARE_HERO_STATE_METHODS(Move);
   DECLARE_HERO_STATE_METHODS(Jump);
   DECLARE_HERO_STATE_METHODS(Fall);

   void (Hero:: *m_onEnter[StateCount])
                  (const Hero::State prevState);
   void (Hero:: *m_onExit[StateCount])
                  (const Hero::State nextState);
   void (Hero:: *m_update[StateCount])(float);

private:
   State m_currentState;

   gr::Sprite m_heroSprite;

   AnimationMgr m_animMgr;

   glm::vec2 m_velocity;

   constexpr static const float JUMP_VEL = -700.f;
};

#endif // HERO_H
