#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include <cmath>

#include "Utility/ResMgr.h"
#include "Collideable.h"
#include "Graphics/Sprite.h"
#include "Hero.h"
#include "Graphics/Drawable.h"

#define DECLARE_SPHERE_STATE_METHODS(stateName) \
   void stateName##_onEnter(const State); \
   void stateName##_onExit(const State); \
   void stateName##_update(float);

class Sphere
      : public Collideable,
        public gr::Drawable
{
public:
   enum State
   {
      State_Idle,
      State_Thrown,
      State_Return,

      StateCount
   };

public:
   explicit Sphere(Hero* _owner);

   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void draw() const override;
   void update(float dt);
   void changeState(const State _newState);

   State getState() { return m_currentState; }
   glm::vec2 getPosition() { return m_sprite.getPosition(); }

   void setDirection(glm::vec2 _dir) { m_direction = _dir; }

private:
   DECLARE_SPHERE_STATE_METHODS(Idle)
   DECLARE_SPHERE_STATE_METHODS(Thrown)
   DECLARE_SPHERE_STATE_METHODS(Return)

   void (Sphere:: *m_onEnter[StateCount])(const State);
   void (Sphere:: *m_onExit[StateCount])(const State);
   void (Sphere:: *m_update[StateCount])(float);

private:
   gr::Sprite m_sprite;

   glm::vec2 m_direction;
   float m_startVelociy;
   float m_velocity;
   Hero* m_owner;
   State m_currentState;
};

#endif // SPHERE_H
