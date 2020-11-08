#include "../include/Entity.h"

Entity::Entity()
{
	sprite = nullptr;
	movementSpeed = 0.f;
}

Entity::~Entity()
{
}

void Entity::move(const float dt, float dir)
{
	
}

void Entity::update(const float dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if(sprite != nullptr)
		target->draw(*sprite);
}

const sf::Vector2f Entity::getPosition() const
{
	return sprite->getPosition();
}
