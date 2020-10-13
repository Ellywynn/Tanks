#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Button
{
public:
	Button();
	~Button();

	sf::RectangleShape border;
	sf::Font* font;
	sf::Text buttonText;

private:
	sf::Color idleColor;
	sf::Color activeColor;
	sf::Color hoverColor;
};

#endif