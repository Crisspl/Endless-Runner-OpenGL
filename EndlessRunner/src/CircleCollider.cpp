#include "CircleCollider.h"
#include "RectsCollider.h"
#include "BoxCollider.h"

CircleCollider::CircleCollider(glm::vec2 _center, float _radius) : Collider(Collider::Circle),
                                                                   m_center(_center),
                                                                   m_radius(_radius)
{}

bool CircleCollider::isCollision(const CircleCollider& _collider) const
{
   float dist = distance(m_center, _collider.getCenter());

   if( dist <= (m_radius + _collider.getRadius()) )
         return true;

   return false;
}

bool CircleCollider::isCollision(const RectsCollider& _collider) const
{
   for(short i = 0; i < _collider.getRectsCount(); i++)
   {
      const ut::Rect& rect = _collider[i];
      glm::vec2 halfExtens = rect.getSize() / 2.f;
      glm::vec2 rectCenter = rect.botLeft() + halfExtens;
      glm::vec2 distanceVec = m_center - rectCenter;

      glm::vec2 clamped = glm::clamp(distanceVec, -halfExtens, halfExtens);
      glm::vec2 closest = rectCenter + clamped;

      if(distance(closest, m_center) < m_radius)
         return true;
   }
   return false;
}

bool CircleCollider::isCollision(const BoxCollider& _collider) const
{
	for (const auto & vert : _collider.getRect().getVerts())
		if (distance(m_center, vert) <= m_radius)
			return true;
}

bool CircleCollider::contains(glm::vec2 _p) const
{
   return distance(_p, m_center) <= m_radius;
}

float CircleCollider::distance(const glm::vec2 a, const glm::vec2 b) const
{
   return glm::length(a - b);
}
