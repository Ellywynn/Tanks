#ifndef PLAYERTIER1TANK_H
#define PLAYERTIER1TANK_H

#include "../Tank.h"

class PlayerTier1Tank : public Tank
{
public:
	PlayerTier1Tank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles);
	~PlayerTier1Tank();

	void shoot(const sf::Vector2f& velocity) override;
};

#endif