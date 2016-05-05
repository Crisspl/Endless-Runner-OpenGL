#pragma once
#include <glm/glm.hpp>
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
   RectsCollider(std::vector<ut::Rect> _rects);
   ~RectsCollider(){ }

public:
   virtual bool isCollision(const CircleCollider& _collider) const override;
   virtual bool isCollision(const RectsCollider& _collider) const override;
   virtual bool isCollision(const BoxCollider& _collider) const override { return false; }

   ut::Rect operator[](unsigned _index) const;
   unsigned getRectsCount() const { return m_vecRects.size(); }

private:
   std::vector<ut::Rect> m_vecRects;
};
