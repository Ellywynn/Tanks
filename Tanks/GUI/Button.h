#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum class ButtonState 
{
	IDLE = 0,
	HOVER,
	ACTIVE
};

class Button
{
public:
	// Constructor
	Button(const std::string& btnText, float x, float y, 
		sf::Font* buttonFont, float w = 100.f, float h = 50.f);

	// Destructor
	~Button();

	// Variables
	sf::RectangleShape border;
	sf::Text buttonText;
	sf::Font* font;
public: // Functions
	void update(sf::Event& event, const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);

	void reset();
	sf::Vector2f getPosition() const;
	const bool isButtonPressed() const;
private: // Variables
	sf::Color idleColor;
	sf::Color activeColor;
	sf::Color hoverColor;

	ButtonState currentState;

	void changeColor();
};

#endif