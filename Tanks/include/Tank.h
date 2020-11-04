#ifndef TANK_H
#define TANK_H

#include "State.h"

enum class TankType {
	Player = 0,
	Enemy
};

class Tank : protected Entity
{
public:
	Tank();
	virtual ~Tank();

	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget* target);
	virtual void move(const float dt, float dir) = 0;
protected:
	sf::Sprite head;
	sf::Sprite body;

	float rotationSpeed;

	sf::Clock attackClock;
	sf::Time attackSpeed;

	float hp;
	float armor;

	TankType type;
};

#endif