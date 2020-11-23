#include "Checkbox.h"

Checkbox::Checkbox(float size, float x, float y,
	bool value)
{
	borderIdle = sf::Color::Black;
	borderHover = sf::Color(25, 25, 25);

	checkmarkIdle = sf::Color(75, 75, 75);
	checkmarkHover = sf::Color(120, 120, 120);

	border.setSize(sf::Vector2f(size, size));
	border.setPosition(x, y);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(4.f);
	border.setOutlineColor(borderIdle);

	checkmark.setSize(sf::Vector2f(size * 0.88f, size * 0.88f));
	checkmark.setOrigin(checkmark.getSize() / 2.f);
	checkmark.setPosition(border.getPosition().x + border.getSize().x / 2.f,
		border.getPosition().y + border.getSize().y / 2.f);
	checkmark.setFillColor(checkmarkIdle);

	selected = value;
	lock = false;
	changed = false;
}

Checkbox::~Checkbox()
{
}

void Checkbox::update(const float dt, sf::Vector2i& mousePosition)
{
	if (border.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		border.setOutlineColor(borderHover);
		if (selected)
		{
			checkmark.setFillColor(checkmarkHover);
		}

		if (!lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			selected = !selected;
			changed = true;
			lock = true;
		}
		else if(lock && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			lock = false;
		}
	}
	else
	{
		border.setOutlineColor(borderIdle);
		checkmark.setFillColor(checkmarkIdle);
	}
}

void Checkbox::render(sf::RenderTarget* target)
{
	target->draw(border);
	if (selected)
	{
		target->draw(checkmark);
	}
}

sf::Vector2f Checkbox::getPosition() const
{
	return border.getPosition();
}

bool Checkbox::isSelected() const
{
	return selected;
}

bool Checkbox::isChanged() const
{
	return changed;
}

void Checkbox::resetChange()
{
	changed = false;
}

void Checkbox::set(bool value)
{
	selected = value;
}
