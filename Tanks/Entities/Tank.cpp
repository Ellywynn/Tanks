#include "Tank.h"

Tank::Tank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles)
{
	this->textures = textures;
	this->projectiles = projectiles;
}

Tank::~Tank()
{
}

void Tank::render(sf::RenderTarget* target)
{
	target->draw(body);
	target->draw(head);
}

void Tank::restartClock()
{
	attackClock.restart();
}

float Tank::getSpeed() const
{
	return movementSpeed;
}

bool Tank::canShoot() const
{
	return attackClock.getElapsedTime() >= attackSpeed;
}
