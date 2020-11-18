#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <SFML/Graphics.hpp>

class Checkbox
{
public:
	Checkbox(float size, float x, float y,
		bool value = false);
	~Checkbox();

	void update(const float dt, sf::Vector2i& mousePosition);
	void render(sf::RenderTarget* target);


	sf::Vector2f getPosition() const;
	bool isSelected() const;
	bool isChanged() const;
	void resetChange();
	void set(bool value);
private:
	bool selected;
	bool lock;
	bool changed;

	sf::RectangleShape border;
	sf::RectangleShape checkmark;

	sf::Color borderIdle;
	sf::Color borderHover;

	sf::Color checkmarkIdle;
	sf::Color checkmarkHover;
};

#endif