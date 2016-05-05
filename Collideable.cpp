#include "Collideable.h"

bool Collideable::isCollision(Collideable& _colliding)
{
   std::shared_ptr<Collider> myColliderPtr( this->getCollider(_colliding.getObjType()) );
   std::shared_ptr<Collider> outerCollider( _colliding.getCollider(this->getObjType()) );

   bool collided(false);

   if(RectsCollider* convertedCollider = dynamic_cast<RectsCollider*>(outerCollider.get()))
   {
      collided = myColliderPtr->isCollision(*convertedCollider);
   }
   else if(CircleCollider* convertedCollider = dynamic_cast<CircleCollider*>(outerCollider.get()))
   {
      collided = myColliderPtr->isCollision(*convertedCollider);
   }
   else if(BoxCollider* convertedCollider = dynamic_cast<BoxCollider*>(outerCollider.get()))
   {
      collided = myColliderPtr->isCollision(*convertedCollider);
   }
   if(collided)
   {
      _colliding.onCollision(this->getObjType());
      this->onCollision(_colliding.getObjType());
   }

   return collided;
}
