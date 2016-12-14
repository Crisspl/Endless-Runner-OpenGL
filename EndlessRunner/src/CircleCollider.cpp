#include "CircleCollider.h"
#include "RectsCollider.h"
#include "BoxCollider.h"
#include "Maths/Maths_funcs.h"

CircleCollider::CircleCollider(fhl::Vec2f _center, float _radius) : Collider(Collider::Circle),
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
      const fhl::Rect& rect = _collider[i];
	  fhl::Vec2f halfExtens = rect.getSize() / 2.f;
	  fhl::Vec2f rectCenter = rect.botLeft() + halfExtens;
	  fhl::Vec2f distanceVec = m_center - rectCenter;

	  fhl::Vec2f clamped = fhl::clamp(distanceVec, -halfExtens, halfExtens);
	  fhl::Vec2f closest = rectCenter + clamped;

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
	return false;
}

bool CircleCollider::contains(fhl::Vec2f _p) const
{
   return distance(_p, m_center) <= m_radius;
}

float CircleCollider::distance(const fhl::Vec2f a, const fhl::Vec2f b) const
{
   return (b - a).length();
}
