#include "Coin.h"

Coin::Coin()
	: m_animMgr(&m_sprite, 0.2f, {40, 40}),
	  m_elapsedTime(0.f),
	  m_currCell(sup::getRand(0, 3))
{
	setOrigin({ 20, 20 });
	m_sprite.setTexture(fhl::ResMgr::loadTexture("Resources/Tex/coin.png", "coinTex"), 0);
	m_sprite.setSize({ 40, 40 });
	m_sprite.setTextureRect(fhl::Rect({ 0, 0 }, { 40, 40 }));
}

void Coin::update(float _dt)
{
	
	m_elapsedTime += _dt;
	if (m_elapsedTime >= 0.05f)
	{
		m_elapsedTime = 0;
		++m_currCell;
		m_currCell = (m_currCell > 3) ? 0 : m_currCell;
		m_sprite.setTextureRect(fhl::Rect({ 40 * m_currCell, 0 }, { 40, 40 }));
	}
	
	//m_animMgr.update(_dt);
}

void Coin::draw(const fhl::DrawConf &) const
{
	fhl::DrawConf conf;
	conf += getTransform();
	fhl::draw(m_sprite, conf);
}

std::shared_ptr<Collider> Coin::getCollider(Collideable::CollideableObjType)
{
	return std::shared_ptr<Collider>(new CircleCollider(getPosition(), 20.f));
}
