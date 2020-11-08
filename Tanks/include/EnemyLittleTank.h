#ifndef ENEMYLITTLETANK_H
#define ENEMYLITTLETANK_H

#include "EnemyTank.h"

class EnemyLittleTank : EnemyTank
{
public:
	EnemyLittleTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles);
	~EnemyLittleTank();
};

#endif