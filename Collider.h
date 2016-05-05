#pragma once

class CircleCollider;
class RectsCollider;
class BoxCollider;

class Collider
{
public:
   enum Type
   {
      Circle,
      Rects,
      Box,

      CountColliderTypes
   };

protected:
   Collider(Type _type) : type(_type){}

public:
   virtual ~Collider(){}

public:
   virtual bool isCollision(const CircleCollider& _collider) const = 0;
   virtual bool isCollision(const RectsCollider& _collider) const = 0;
   virtual bool isCollision(const BoxCollider& _collider) const = 0;

   Type type;
};

