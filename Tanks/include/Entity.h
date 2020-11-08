#ifndef ENTITY_H
#define ENTITY_H

#include "ResourceHolder.h"
#include "Hitbox.h"

class Entity
{
protected:
	sf::Sprite* sprite;
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	virtual void move(const float dt, float dir = 1.f);
	virtual void update(const float dt);
	virtual void render(sf::RenderTarget* target);

	virtual const sf::Vector2f getPosition() const;
};

#endif