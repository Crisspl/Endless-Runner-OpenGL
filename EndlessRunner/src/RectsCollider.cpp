#include "RectsCollider.h"

#include "CircleCollider.h"

RectsCollider::RectsCollider(std::vector<fhl::Rect> _rects)
                        : Collider(Collider::Rects),
                          m_vecRects(_rects)
{

}

bool RectsCollider::isCollision(const CircleCollider& _collider) const
{
   return _collider.isCollision(*this);
}

bool RectsCollider::isCollision(const RectsCollider& _collider) const
{
   for(unsigned i = 0; i < m_vecRects.size(); i++)
   {
      for(unsigned j = 0; j < _collider.getRectsCount(); j++)
      {
         if(m_vecRects[i].intersects(_collider[j]))
               return true;
      }
   }
   return false;
}

fhl::Rect RectsCollider::operator[](unsigned _index) const
{
   return m_vecRects[_index];
}
