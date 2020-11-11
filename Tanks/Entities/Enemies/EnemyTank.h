#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "../Tank.h"


class EnemyTank : public Tank 
{
public:
	EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles, Tank* player);
	virtual ~EnemyTank();

	virtual void update(const float dt) = 0;

	Tank* player;
	bool rotateLeft;
	bool shooting;
	bool rotating;
};

#endif