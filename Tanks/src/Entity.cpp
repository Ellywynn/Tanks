#include "../include/Entity.h"

Entity::Entity()
{
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
	target->draw(shape);
}
