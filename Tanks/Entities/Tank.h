#ifndef TANK_H
#define TANK_H

#include "../States/State.h"
#include "../Projectiles/StandartBullet.h"


enum class TankType 
{
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

	ResourceHolder<sf::Texture, Textures>* textures;
	std::vector<Projectile*>* projectiles;

	// Tank objects
	sf::Sprite head;
	sf::Sprite body;
	Hitbox hb_body;
	Hitbox hb_head;

	// Stats
	float rotationSpeed;
	float hp;
	float armor;
	float damage;
	sf::Time attackSpeed;

	TankType type;

	void restartClock();
	float getSpeed() const;
	bool canShoot() const;
protected:
	sf::Clock attackClock;
};

#endif