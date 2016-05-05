#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "Collider.h"
#include "Utility/OrientedRect.h"

namespace ut { class Rect; }

class BoxCollider
   : public Collider
{
public:
   explicit BoxCollider(ut::OrientedRect _rect);

   bool isCollision(const CircleCollider& _collider) const override;
   bool isCollision(const RectsCollider& _collider) const override;
   bool isCollision(const BoxCollider& _collider) const override;

   const ut::OrientedRect& getRect() const { return m_rect; }

private:
   ut::OrientedRect m_rect;
};
