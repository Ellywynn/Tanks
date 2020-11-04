#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>

class Hitbox
{
public:
	Hitbox();
	Hitbox(float width, float height);
	Hitbox(float width, float height, float x, float y);

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setSize(float x, float y);
	void setColor(sf::Color color);
	void setRotation(float angle);
	void setThickness(float thickness);

	void move(float x, float y);
	void move(const sf::Vector2f& velocity);

	const sf::RectangleShape get() const;
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
private:
	sf::RectangleShape hitbox;
};

#endif