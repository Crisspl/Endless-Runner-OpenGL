#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <glm/glm.hpp>
#include <cmath>
#include <iostream>

#include "Collider.h"

class RectsCollider;
class BoxCollider;

class CircleCollider
   :public Collider
{
public:
   CircleCollider(glm::vec2 center, float radius);
   ~CircleCollider() { }

public:
   virtual bool isCollision(const CircleCollider& _collider) const override;
   virtual bool isCollision(const RectsCollider& _collider) const override;
   virtual bool isCollision(const BoxCollider& _collider) const override;

   bool contains(glm::vec2 _p) const;

   glm::vec2 getCenter() const { return m_center; }
   float getRadius() const { return m_radius; }

private:
   float distance(const glm::vec2 a, const glm::vec2 b) const;

private:
   glm::vec2 m_center;
   float m_radius;

};

#endif // CIRCLECOLLIDER_H
