#ifndef ENTITY_H
#define ENTITY_H

#include "ResourceHolder.h"

class Entity
{
protected:
	sf::RectangleShape shape;
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	virtual void move(const float dt, float dir = 1.f);
	virtual void update(const float dt);
	virtual void render(sf::RenderTarget* target);
};

#endif