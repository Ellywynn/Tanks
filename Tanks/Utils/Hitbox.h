#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "SAT.h"

class Hitbox
{
public:
	// Constructors
	Hitbox();
	Hitbox(float width, float height);
	Hitbox(float width, float height, float x, float y);
	~Hitbox();

	void move(float x, float y);
	void move(const sf::Vector2f& velocity);

	// Setters
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setSize(float x, float y);
	void setColor(sf::Color color);
	void setRotation(float angle);
	void setThickness(float thickness);

	// Getters
	const sf::RectangleShape get() const;
	const sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	bool collides(Hitbox& target);
private:
	sf::RectangleShape hitbox;
};

#endif