#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "../Tank.h"

class EnemyTank : Tank 
{
public:
	EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles);
	virtual ~EnemyTank();
};

#endif