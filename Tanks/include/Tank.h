#ifndef TANK_H
#define TANK_H

#include "State.h"

class Tank : protected Entity
{
public:
	Tank();
	virtual ~Tank();

	virtual void update(const float dt);
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
};

#endif