#ifndef COIN_H
#define COIN_H

#include "Graphics/DrawFuncs.h"
#include "Graphics/Drawable.h"
#include "Graphics/Transformable.h"
#include "Graphics/Sprite.h"
#include "Graphics/ResMgr.h"
#include "Collideable.h"
#include "CircleCollider.h"
#include "AnimationMgr.h"
#include "Global.h"
#include "SoundMgr.h"

class Coin
	: public fhl::Drawable,
	  public fhl::Transformable,
	  public Collideable
{
public:
	Coin();

	void update(float _dt);
	void draw(const fhl::DrawConf &) const override;
	std::shared_ptr<Collider> getCollider(Collideable::CollideableObjType) override;
	void onCollision(Collideable::CollideableObjType) override;

private:
	fhl::Sprite m_sprite;
	AnimationMgr m_animMgr;
	float m_elapsedTime;
	size_t m_currCell;
	//sf::Sound m_gatherSound;
};

#endif // COIN_H