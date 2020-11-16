#include "Slider.h"

Slider::Slider(float w, float h, float x, float y, int minValue,
	int maxValue, sf::Vector2i* mousePos,
	const std::string& measure, const std::string& sliderName)
	:font(nullptr)
{
	this->mousePosition = mousePos;

	strip.setSize(sf::Vector2f(w, h));
	strip.setOrigin(w / 2.f, h / 2.f);
	strip.setPosition(x, y);
	strip.setOutlineThickness(3.f);
	strip.setOutlineColor(sf::Color(112, 112, 112));

	pointer.setSize(sf::Vector2f(w / 20.f, h * 1.6f));
	pointer.setOrigin(pointer.getSize() / 2.f);

	minCursorPos = strip.getPosition().x - w / 2.f;
	maxCursorPos = strip.getPosition().x + w / 2.f;

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->value = maxValue;

	this->measure = measure;

	changed = false;

	this->sliderName.setString(sliderName);
	this->valueText.setString(std::to_string(value) + measure);

	// the next x coordinate of the pointer
	stepRange = w / (maxValue - minValue);

	stripIdleColor = sf::Color::Black;

	pointerIdleColor = sf::Color(190, 190, 190);
	pointerHoverColor = sf::Color(230, 230, 230);
	pointerActiveColor = sf::Color(75, 75, 75);

	setValue(value);
}

Slider::~Slider()
{
}

void Slider::update(const float dt)
{
	sf::Vector2f mPos = static_cast<sf::Vector2f>(*mousePosition);
	if (strip.getGlobalBounds().contains(mPos))
	{
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
			changed = true;
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

			valueText.setString(std::to_string(value) + measure);
			this->valueText.setPosition(maxCursorPos - valueText.getGlobalBounds().width,
				strip.getPosition().y - strip.getSize().y - pointer.getGlobalBounds().height / 2.f);
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
	if (!sliderName.getString().isEmpty())
		target->draw(sliderName);
	target->draw(valueText);
	target->draw(pointer);
}

void Slider::setValue(int val)
{
	value = val;

	valueText.setString(std::to_string(value) + measure);
	float pointerPosition = maxCursorPos -
		stepRange * (maxValue - value);

	pointer.setPosition(sf::Vector2f(pointerPosition, strip.getPosition().y));
}

void Slider::setFont(sf::Font* font)
{
	this->font = font;
	valueText.setFont(*font);
	sliderName.setFont(*font);

	this->sliderName.setCharacterSize(22u);
	this->sliderName.setPosition(minCursorPos,
		strip.getPosition().y - strip.getSize().y - pointer.getGlobalBounds().height / 2.f - 5.f);

	this->valueText.setCharacterSize(16u);
	this->valueText.setPosition(maxCursorPos - valueText.getGlobalBounds().width,
		strip.getPosition().y - strip.getSize().y - pointer.getGlobalBounds().height / 2.f);
}

void Slider::setName(const std::string& name)
{
	sliderName.setString(name);
}

int Slider::getValue() const
{
	return value;
}

bool Slider::isChanged() const
{
	return changed;
}

void Slider::resetChange()
{
	changed = false;
}
