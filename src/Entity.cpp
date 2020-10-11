#include "../include/Entity.h"

Entity::Entity()
{
	shape.setSize(sf::Vector2f(50.f, 50.f));
	movementSpeed = 100.f;
}

Entity::~Entity()
{
}

void Entity::move(const float dt, const float dx, const float dy)
{
	shape.move(dx * dt * movementSpeed, dy * dt * movementSpeed);
}

void Entity::update(const float dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
