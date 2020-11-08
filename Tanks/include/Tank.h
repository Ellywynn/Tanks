#ifndef TANK_H
#define TANK_H

#include "State.h"
#include "StandartBullet.h"

enum class TankType {
	Player = 0,
	Enemy
};

class Tank : protected Entity
{
public:
	Tank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles);
	virtual ~Tank();

	virtual void render(sf::RenderTarget* target);
	virtual void shoot(const sf::Vector2f& velocity) = 0;

	void restartClock();

	ResourceHolder<sf::Texture, Textures>* textures;
	std::vector<Projectile*>* projectiles;

	sf::Sprite head;
	sf::Sprite body;
	Hitbox hb_body;
	Hitbox hb_head;

	float rotationSpeed;
	float hp;
	float armor;
	float damage;
	sf::Time attackSpeed;

	TankType type;

	float getSpeed() const;
	bool canShoot() const;
protected:
	sf::Clock attackClock;
};

#endif