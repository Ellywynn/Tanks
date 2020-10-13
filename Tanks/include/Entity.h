#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	virtual void move(const float dt, const float dx, const float dy);
	virtual void update(const float dt);
	virtual void render(sf::RenderTarget* target);
};

#endif