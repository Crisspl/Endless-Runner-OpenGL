#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <vector>
#include <iostream>

#include "Collider.h"
#include "Utility/OrientedRect.h"

class BoxCollider
   : public Collider
{
public:
   explicit BoxCollider(fhl::Rect *_rect);
   ~BoxCollider() { delete m_rect; }

   bool isCollision(const CircleCollider& _collider) const override;
   bool isCollision(const RectsCollider& _collider) const override;
   bool isCollision(const BoxCollider& _collider) const override;

   const fhl::Rect& getRect() const { return *m_rect; }

private:
   fhl::Rect *m_rect;
};

#endif // BOXCOLLIDER_H
