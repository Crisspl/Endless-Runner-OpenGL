#include "Hero.h"

#define REGISTER_HERO_STATES(stateName) \
   m_onEnter[State_##stateName] \
     = &Hero::stateName##_onEnter; \
   m_onExit[State_##stateName] \
     = &Hero::stateName##_onExit; \
   m_update[State_##stateName] \
     = &Hero::stateName##_update;

Hero::Hero()
      : Collideable(Collideable::Coll_Hero),
        m_currentState(StateCount),
        m_currentFrameTime(0),
        m_frameCounter(0),
        m_heroSprite(ut::ResMgr::loadTexture("Resources/Tex/hero_sheet.png", "heroTex"))
{
   REGISTER_HERO_STATES(Move)
   REGISTER_HERO_STATES(Jump)
   REGISTER_HERO_STATES(Fall)

   m_heroSprite.setOrigin({25.f, 50.f})
               .rotate(25.f);

   changeState(State_Move);
}

std::shared_ptr<Collider> Hero::getCollider(CollideableObjType _objType)
{
   ut::Rect *rect = new ut::OrientedRect(m_heroSprite.getOBB());

   rect->addHeight(-m_heroSprite.getSize().y * 0.8f)
       .move({0, m_heroSprite.getSize().y * 0.8f});

   return std::shared_ptr<Collider>(new BoxCollider(rect));
}

void Hero::draw() const
{
   m_heroSprite.draw();
}

void Hero::update(float dt)
{
   m_currentFrameTime += dt;
   if(m_currentFrameTime >= SINGLE_FRAME_TIME)
   {
      m_currentFrameTime = 0;
      m_heroSprite.setTextureRect(ut::Rect({m_frameCounter * 50.f, m_currentState * 50.f}, {50.f, 50.f}),
                                  true
                                 );
      if(++m_frameCounter == m_heroSprite.getTexture().getSize().x / 50.f)
         m_frameCounter = 0;
   }
   (this->*m_update[m_currentState])(dt);
}

void Hero::changeState(const Hero::State _newState)
{
   if(m_currentState < StateCount &&
      m_currentState != _newState)
   {
         (this->*m_onExit[m_currentState])(_newState);
   }

   const Hero::State prevState(m_currentState);

   m_currentState = _newState;

   (this->*m_onEnter[m_currentState])(prevState);
}

void Hero::move(glm::vec2 _offset)
{
   m_heroSprite.move(_offset);
}

//////////// MOVE STATE ////////////////////

void Hero::Move_onEnter(Hero::State prevState)
{
   m_velocity = glm::vec2();
}

void Hero::Move_onExit(Hero::State nextState){}

void Hero::Move_update(float dt){}

//////////// JUMP STATE ////////////////////

void Hero::Jump_onEnter(Hero::State prevState)
{
   m_velocity.y = JUMP_VEL;
}

void Hero::Jump_onExit(Hero::State nextState)
{
}

void Hero::Jump_update(float dt)
{
   move(m_velocity * dt);
   m_velocity.y += dt * sup::GRAVITY;
   if(m_velocity.y > 0)
      changeState(State_Fall);
}

//////////// FALL STATE ////////////////////

void Hero::Fall_onEnter(Hero::State prevState)
{

}

void Hero::Fall_onExit(Hero::State nextState)
{

}

void Hero::Fall_update(float dt)
{
   move(m_velocity * dt);
   m_velocity.y += dt * sup::GRAVITY;
}
