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
		idleColor = sf::Color::Black;
		hoverColor = sf::Color(25, 25, 25);

		border.setOutlineThickness(3.f);
		border.setOutlineColor(sf::Color(112, 112, 112));
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
		activeElement.border.setPosition(x, y);

		activeElement.valueText.setFont(*font);

		opened = false;
		lock = false;
		hovered = false;
		changed = false;
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
				hovered = false;
				for (size_t i = 1; i < elements.size(); i++)
				{
					if (!hovered && elements[i]->border.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
					{
						elements[i]->border.setFillColor(elements[i]->hoverColor);
						hovered = true;
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							opened = false;
							elements[0]->value = elements[i]->value;
							elements[0]->valueText.setString(elements[i]->valueText.getString());
							changed = true;
							break;
						}
					}
					else
					{
						elements[i]->border.setFillColor(elements[i]->idleColor);
					}
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
		// if there is no elements in the list, create the first element
		// and push it twice(the first for closed list and the second for 
		if (elements.empty())
		{
			initActiveElement(value, textValue);
			addElement(value, textValue);
		}
		// if there is an element in the list already, just add the new one
		else
		{
			addElement(value, textValue);
		}
	}

	const T& getActiveValue() const
	{
		return elements[0]->value;
	}

	sf::Vector2f getPosition() const
	{
		return elements[0]->border.getPosition();
	}

	void setActiveValue(const T& value, const std::string& name)
	{
		elements[0]->value = value;
		elements[0]->valueText.setString(name);
	}

	void setCharSize(unsigned int size)
	{
		for (auto& e : elements)
		{
			e->valueText.setCharacterSize(size);
			e->valueText.setOrigin(e->valueText.getGlobalBounds().width / 2.f,
				e->valueText.getGlobalBounds().height / 2.f);
			e->valueText.setPosition(e->border.getPosition().x
				+ e->border.getGlobalBounds().width / 2.f,
				e->border.getPosition().y
				+ e->border.getGlobalBounds().height / 2.f
				- 2 * activeElement.border.getOutlineThickness());
		}
	}

	void resetChange()
	{
		changed = false;
	}

	bool isChanged() const
	{
		return changed;
	}
private:
	std::vector<DDL_Element<T>*> elements;
	DDL_Element<T> activeElement;
	bool opened;
	bool lock;
	bool hovered;

	bool changed;

	sf::Font* textFont;

	void addElement(const T& value, const std::string& textValue)
	{
		DDL_Element<T> temp(activeElement);
		temp.value = value;
		temp.valueText.setString(textValue);
		temp.valueText.setOrigin(temp.valueText.getGlobalBounds().width / 2.f,
			temp.valueText.getGlobalBounds().height / 2.f);
		sf::Vector2f newPosition(elements.back()->border.getPosition());
		temp.border.setPosition(newPosition.x, newPosition.y +
			activeElement.border.getSize().y + 2.f*activeElement.border.getOutlineThickness());
		temp.valueText.setPosition(temp.border.getPosition().x
			+ temp.border.getGlobalBounds().width / 2.f,
			temp.border.getPosition().y
			+ temp.border.getGlobalBounds().height / 2.f
			- 2 * activeElement.border.getOutlineThickness());
		elements.push_back(new DDL_Element<T>(temp));
	}

	void initActiveElement(const T& value, const std::string& textValue)
	{
		activeElement.value = value;
		activeElement.valueText.setString(textValue);
		activeElement.valueText.setOrigin(activeElement.valueText.getGlobalBounds().width / 2.f,
			activeElement.valueText.getGlobalBounds().height / 2.f);
		activeElement.valueText.setPosition(activeElement.border.getPosition().x
			+ activeElement.border.getGlobalBounds().width / 2.f,
			activeElement.border.getPosition().y
			+ activeElement.border.getGlobalBounds().height / 2.f - 2 * activeElement.border.getOutlineThickness());
		elements.push_back(new DDL_Element<T>(activeElement));
	}
};

#endif