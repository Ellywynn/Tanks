#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// drop-down list element

template<typename T>
class DDL_Element
{
public:
	DDL_Element()
	{
		idleColor = sf::Color::Green;
		hoverColor = sf::Color::Black;

		border.setOutlineThickness(2.f);
		border.setOutlineColor(sf::Color::Red);
		border.setFillColor(idleColor);

		valueText.setCharacterSize(14u);
		valueText.setStyle(sf::Text::Style::Regular);
	}
	DDL_Element(const T& value)
		: DDL_Element()
	{
		this->value = value;
	}
	~DDL_Element() {}

	T value;
	sf::RectangleShape border;
	sf::Text valueText;

	sf::Color idleColor;
	sf::Color hoverColor;
};

template<typename T>
class DropDownList
{
public:
	DropDownList(float w, float h, float x, float y, sf::Font* font)
	{
		activeElement.border.setSize(sf::Vector2f(w, h));
		activeElement.border.setOrigin(w / 2.f, h / 2.f);
		activeElement.border.setPosition(x, y);

		activeElement.valueText.setFont(*font);

		opened = false;
		lock = false;
		textFont = font;
	}
	~DropDownList()
	{
		for (auto& e : elements)
			delete e;
	}

	void update(const float dt, const sf::Vector2i& mousePos, const sf::Event event)
	{
		if (!elements.empty())
		{
			if (elements[0]->border.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
			{
				if (!lock && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
				{
					opened = !opened;
					lock = true;
				}
				else if (lock && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					lock = false;
				}
			}

			if (opened)
			{
				for (int i = 1; i < elements.size(); i++)
				{
					if (elements[i]->border.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
					{
						elements[i]->border.setFillColor(elements[i]->hoverColor);
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							std::cout << "CHANGED\n";
							opened = false;

							elements[0]->value = elements[i]->value;
							elements[0]->valueText.setString(elements[i]->valueText.getString());
						}
					}
					else
						elements[i]->border.setFillColor(elements[i]->idleColor);
				}
			}
		}
	}

	void render(sf::RenderTarget* target)
	{

		target->draw(elements[0]->border);
		target->draw(elements[0]->valueText);
		if (opened)
		{
			for (auto& e : elements)
			{
				target->draw(e->border);
				target->draw(e->valueText);
			}
		}
	}

	void add(const T& value, const std::string& textValue)
	{
		// if there is no elements in the list, add the first element
		if (elements.empty())
		{
			activeElement.value = value;
			activeElement.valueText.setString(textValue);
			activeElement.valueText.setOrigin(activeElement.valueText.getGlobalBounds().width / 2.f,
				activeElement.valueText.getGlobalBounds().height / 2.f);
			activeElement.valueText.setPosition(activeElement.border.getPosition());
			elements.push_back(new DDL_Element<T>(activeElement));

			DDL_Element<T> temp(activeElement);
			temp.value = value;
			temp.valueText.setString(textValue);
			temp.valueText.setOrigin(temp.valueText.getGlobalBounds().width / 2.f,
				temp.valueText.getGlobalBounds().height / 2.f);
			sf::Vector2f newPosition(elements.back()->border.getPosition());
			temp.border.setPosition(newPosition.x, newPosition.y +
				activeElement.border.getSize().y + activeElement.border.getOutlineThickness());
			temp.valueText.setPosition(temp.border.getPosition());
			elements.push_back(new DDL_Element<T>(temp));
		}
		else
		{
			DDL_Element<T> temp(activeElement);
			temp.value = value;
			temp.valueText.setString(textValue);
			temp.valueText.setOrigin(temp.valueText.getGlobalBounds().width / 2.f,
				temp.valueText.getGlobalBounds().height / 2.f);
			sf::Vector2f newPosition(elements.back()->border.getPosition());
			temp.border.setPosition(newPosition.x, newPosition.y +
				activeElement.border.getSize().y + activeElement.border.getOutlineThickness());
			temp.valueText.setPosition(temp.border.getPosition());
			elements.push_back(new DDL_Element<T>(temp));
		}
	}

	const T& getActiveValue() const
	{
		return elements[0]->value;
	}
private:
	std::vector<DDL_Element<T>*> elements;
	DDL_Element<T> activeElement;
	bool opened;
	bool lock;

	sf::Font* textFont;
};

#endif