#include "Slider.h"

Slider::Slider(float w, float h, float x, float y, float minValue,
	float maxValue, sf::Vector2i* mousePos)
	:font(nullptr)
{
	this->mousePosition = mousePos;

	strip.setSize(sf::Vector2f(w, h));
	strip.setOrigin(w / 2.f, h / 2.f);
	strip.setPosition(x, y);
	strip.setOutlineThickness(2.f);
	strip.setOutlineColor(sf::Color::Cyan);

	pointer.setSize(sf::Vector2f(5.f, h * 1.5f));
	pointer.setOrigin(pointer.getSize() / 2.f);

	minCursorPos = strip.getPosition().x - w / 2.f;
	maxCursorPos = strip.getPosition().x + w / 2.f;

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->value = maxValue;

	// the next x coordinate of the pointer
	stepRange = w/(maxValue - minValue);

	stripIdleColor = sf::Color::Red;
	stripHoverColor = sf::Color::Yellow;

	pointerIdleColor = sf::Color::Magenta;
	pointerHoverColor = sf::Color::Black;
	pointerActiveColor = sf::Color::Green;

	float pointerPosition = maxCursorPos -
		stepRange * (maxValue - value);

	pointer.setPosition(sf::Vector2f(pointerPosition, y));
}

Slider::~Slider()
{
}

void Slider::update(const float dt)
{
	sf::Vector2f mPos = static_cast<sf::Vector2f>(*mousePosition);
	if (strip.getGlobalBounds().contains(mPos))
	{
		strip.setFillColor(stripHoverColor);

		if (pointer.getGlobalBounds().contains(mPos))
		{
			pointer.setFillColor(pointerHoverColor);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				pointer.setFillColor(pointerActiveColor);
			}
		}
		else
		{
			pointer.setFillColor(pointerIdleColor);
		}

		// pointer position
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pointer.setFillColor(pointerActiveColor);
			/*
				Finding current value by current coordinates:
				1. Find the relation between current cursor point and full lenght:
					0|----c-----------------|100
					We are dividing [0:c] by [0:100] and get percentage.
				2. Multiply this value by min and max value difference.
				3. Add the minimum value to the result.
			*/
			value = (mPos.x - (minCursorPos)) / (maxCursorPos - minCursorPos) * (maxValue - minValue) + minValue;

			if (value < minValue) value = minValue;
			if (value > maxValue) value = maxValue;

			/*
				Finding current pointer position by value:
				1. We are finding the range that pointer passes from start
				2. We substract this range from the end of the slider
			*/
			float pointerPos = maxCursorPos - stepRange * (maxValue - value);
			pointer.setPosition(pointerPos, pointer.getPosition().y);
		}
	}
	else
	{
		strip.setFillColor(stripIdleColor);
		pointer.setFillColor(pointerIdleColor);
	}
}

void Slider::render(sf::RenderTarget* target)
{
	target->draw(strip);
	target->draw(pointer);
}

void Slider::setValue(float val)
{
	value = val;

	float pointerPosition = maxCursorPos -
		stepRange * (maxValue - value);

	pointer.setPosition(sf::Vector2f(pointerPosition, pointer.getPosition().y));
}

float Slider::getValue() const
{
	return 0.0f;
}
