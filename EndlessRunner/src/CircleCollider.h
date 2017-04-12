#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <cmath>
#include <iostream>

#include <FHL/Maths/vectors.h>

#include "Collider.h"

class RectsCollider;
class BoxCollider;

class CircleCollider
   :public Collider
{
public:
   CircleCollider(fhl::Vec2f center, float radius);
   ~CircleCollider() { }

public:
   virtual bool isCollision(const CircleCollider& _collider) const override;
   virtual bool isCollision(const RectsCollider& _collider) const override;
   virtual bool isCollision(const BoxCollider& _collider) const override;

   bool contains(fhl::Vec2f _p) const;

   fhl::Vec2f getCenter() const { return m_center; }
   float getRadius() const { return m_radius; }

private:
   float distance(const fhl::Vec2f a, const fhl::Vec2f b) const;

private:
	fhl::Vec2f m_center;
   float m_radius;

};

#endif // CIRCLECOLLIDER_H
