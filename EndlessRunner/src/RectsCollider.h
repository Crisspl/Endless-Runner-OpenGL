#ifndef RECTSCOLLIDER_H
#define RECTSCOLLIDER_H

#include <cmath>
#include <vector>
#include "Collider.h"
#include "Utility/Rect.h"

class CircleCollider;
class BoxCollider;

class RectsCollider
   : public Collider
{
public:
   RectsCollider(std::vector<fhl::Rect> _rects);
   ~RectsCollider(){ }

public:
   virtual bool isCollision(const CircleCollider& _collider) const override;
   virtual bool isCollision(const RectsCollider& _collider) const override;
   virtual bool isCollision(const BoxCollider& _collider) const override { return false; }

   fhl::Rect operator[](unsigned _index) const;
   unsigned getRectsCount() const { return m_vecRects.size(); }

private:
   std::vector<fhl::Rect> m_vecRects;
};

#endif // RECTSCOLLIDER_H
