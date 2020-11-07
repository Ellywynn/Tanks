#include "../include/Hitbox.h"

Hitbox::Hitbox()
{
	hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);
}

Hitbox::Hitbox(float width, float height)
	:Hitbox()
{
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setOrigin(hitbox.getSize().x / 2.f,
		hitbox.getSize().y / 2.f);
}

Hitbox::Hitbox(float width, float height, float x, float y)
	: Hitbox(width, height)
{
	hitbox.setPosition(x, y);
}

void Hitbox::setPosition(float x, float y)
{
	hitbox.setPosition(x, y);
}

void Hitbox::setPosition(const sf::Vector2f& position)
{
	hitbox.setPosition(position);
}

void Hitbox::setSize(float x, float y)
{
	hitbox.setSize(sf::Vector2f(x, y));
	hitbox.setOrigin(x / 2.f, y / 2.f);
}

void Hitbox::setColor(sf::Color color)
{
	hitbox.setOutlineColor(color);
}

void Hitbox::setRotation(float angle)
{
	hitbox.setRotation(angle);
}

void Hitbox::setThickness(float thickness)
{
	hitbox.setOutlineThickness(thickness);
}

void Hitbox::move(float x, float y)
{
	hitbox.move(x, y);
}

void Hitbox::move(const sf::Vector2f& velocity)
{
	hitbox.move(velocity);
}

const sf::RectangleShape Hitbox::get() const
{
	return hitbox;
}

const sf::Vector2f Hitbox::getPosition() const
{
	return hitbox.getPosition();
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}
