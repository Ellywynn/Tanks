#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Slider
{
public:
	Slider(float w, float h, float x, float y, int minValue, int maxValue,
		sf::Vector2i* mousePos,
		const std::string& measure = "", const std::string& sliderName = "");
	~Slider();

	void update(const float dt);
	void render(sf::RenderTarget* target);

	void setValue(int val);
	void setFont(sf::Font* font);
	void setName(const std::string& name);

	int getValue() const;
	bool isChanged() const;
	void resetChange();
private:
	sf::Vector2i* mousePosition;

	sf::RectangleShape strip;
	sf::RectangleShape pointer;

	float maxCursorPos;
	float minCursorPos;

	sf::Text valueText;
	sf::Text sliderName;
	std::string measure;
	sf::Font* font;

	int value;
	int minValue;
	int maxValue;

	float stepRange;

	sf::Color stripIdleColor;
	sf::Color stripHoverColor;

	sf::Color pointerIdleColor;
	sf::Color pointerHoverColor;
	sf::Color pointerActiveColor;

	bool changed;
};

#endif