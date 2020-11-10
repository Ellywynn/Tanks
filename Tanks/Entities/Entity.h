#ifndef ENTITY_H
#define ENTITY_H

#include "../Utils/ResourceHolder.h"
#include "../Utils/Hitbox.h"

class Entity
{
protected:
	sf::Sprite* sprite;				// Entity sprite
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	// Functions
	virtual void move(const float dt, float dir = 1.f);
	virtual void update(const float dt);
	virtual void render(sf::RenderTarget* target);

	virtual const sf::Vector2f getPosition() const;
};

#endif