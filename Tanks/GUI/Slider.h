#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Slider
{
public:
	Slider(float w, float h, float x, float y, float minValue, float maxValue,
		sf::Vector2i* mousePos);
	~Slider();

	void update(const float dt);
	void render(sf::RenderTarget* target);

	sf::Text valueText;
	sf::Text sliderText;

	void setValue(float val);

	float getValue() const;
private:
	sf::Vector2i* mousePosition;

	sf::RectangleShape strip;
	sf::RectangleShape pointer;

	float maxCursorPos;
	float minCursorPos;

	sf::Font* font;

	float value;
	float minValue;
	float maxValue;

	float stepRange;

	sf::Color stripIdleColor;
	sf::Color stripHoverColor;

	sf::Color pointerIdleColor;
	sf::Color pointerHoverColor;
	sf::Color pointerActiveColor;
};

#endif