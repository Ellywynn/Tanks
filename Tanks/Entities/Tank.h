#ifndef TANK_H
#define TANK_H

#include "../States/State.h"
#include "../Projectiles/StandartBullet.h"


enum class TankType 
{
	Player = 0,
	Enemy
};

class Tank : public Entity
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
	float hp;
	float armor;
	float damage;
	float rotationSpeed;
	sf::Time attackSpeed;

	TankType type;

	void takeDamage(float dmg);

	void restartClock();
	float getSpeed() const;
	bool canShoot() const;
	bool isAlive() const;
protected:
	sf::Clock attackClock;
};

#endif