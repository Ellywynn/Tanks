#ifndef STANDARTBULLET_H
#define STANDARTBULLET_H

#include "Projectile.h"

class StandartBullet : public Projectile
{
public:
	StandartBullet(ProjectileType type, const sf::Texture& texture,
		const sf::Vector2f& spawnPoint, const sf::Vector2f& direction, float angle);
	~StandartBullet();

	void update(const float dt) override;
};

#endif