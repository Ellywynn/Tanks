#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum class ButtonState {
	IDLE = 0,
	HOVER,
	ACTIVE
};

class Button
{
public:
	Button(const std::string& btnText, float x, float y, 
		sf::Font* buttonFont, float w = 100.f, float h = 50.f);
	~Button();

	sf::RectangleShape border;
	sf::Text buttonText;
	sf::Font* font;
public:
	void update(sf::Event& event, sf::Vector2i mousePos);
	void render(sf::RenderTarget& target);

	const bool isButtonPressed() const;
private:
	sf::Color idleColor;
	sf::Color activeColor;
	sf::Color hoverColor;

	ButtonState currentState;
};

#endif