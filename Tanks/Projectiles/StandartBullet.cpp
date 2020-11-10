#include "StandartBullet.h"

StandartBullet::StandartBullet(ProjectileType type, const sf::Texture& texture,
	const sf::Vector2f& spawnPoint, const sf::Vector2f& direction, float angle)
	:Projectile(type)
{
	sprite = new sf::Sprite(texture);
	sprite->setScale(sf::Vector2f(0.1f, 0.1f));
	sprite->setOrigin(sprite->getGlobalBounds().width / 2.f,
		sprite->getGlobalBounds().height / 2.f);
	sprite->setPosition(spawnPoint);
	sprite->setRotation(angle - 180.f);

	hitbox.setSize(texture.getSize().x * sprite->getScale().x,
		texture.getSize().y * sprite->getScale().y);
	hitbox.setRotation(angle - 180.f);

	float ang = atan2(direction.y, direction.x);
	float x = std::cos(ang);
	float y = std::sin(ang);
	sf::Vector2f pos(x * 50.f - y * 20.f, y * 50.f + x * 20.f);
	hitbox.setPosition(sprite->getPosition() + pos);

	this->direction = direction;
	movementSpeed = 100.f;
}

StandartBullet::~StandartBullet()
{
	delete sprite;
}

void StandartBullet::update(const float dt)
{
	sprite->move(direction * dt * movementSpeed);
	hitbox.move(direction * dt * movementSpeed);
}