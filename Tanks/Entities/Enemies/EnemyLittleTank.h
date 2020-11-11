#ifndef ENEMYLITTLETANK_H
#define ENEMYLITTLETANK_H

#include "EnemyTank.h"

class EnemyLittleTank : public EnemyTank
{
public:
	EnemyLittleTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles, Tank* player);
	~EnemyLittleTank();

	void update(const float dt) override;
	void shoot(const sf::Vector2f& velocity) override;
};

#endif