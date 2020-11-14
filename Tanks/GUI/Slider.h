#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Slider
{
public:
	Slider(float w, float h, float x, float y,
		float initValue, float minValue, float maxValue,
		sf::Vector2i* mousePos);
	~Slider();

	void update(const float dt);
	void render(sf::RenderTarget* target);

	sf::Vector2i* mousePosition;

	sf::RectangleShape strip;
	sf::RectangleShape pointer;

	float maxCursorPos;
	float minCursorPos;

	sf::Text valueText;
	sf::Font* font;

	float value;
	float minValue;
	float maxValue;

	float stepRange;

	float getValue() const;
private:
	sf::Color stripIdleColor;
	sf::Color stripHoverColor;

	sf::Color pointerIdleColor;
	sf::Color pointerHoverColor;
	sf::Color pointerActiveColor;
};

#endif