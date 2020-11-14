#include "Button.h"

Button::Button(const std::string& btnText, float x, float y,
	sf::Font* buttonFont, float w, float h)
{
	idleColor = sf::Color::Red;
	hoverColor = sf::Color::Yellow;
	activeColor = sf::Color::Green;

	border.setSize(sf::Vector2f(w, h));
	border.setPosition(x, y);
	border.setFillColor(idleColor);

	font = buttonFont;
	buttonText.setString(btnText);
	buttonText.setFont(*font);
	buttonText.setCharacterSize(14u);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f,
		buttonText.getGlobalBounds().height / 2.f);
	buttonText.setPosition(border.getPosition().x + border.getSize().x / 2.f,
		border.getPosition().y + border.getSize().y / 2.f);

	currentState = ButtonState::IDLE;
}

Button::~Button()
{
	
}

void Button::update(sf::Event& event, const sf::Vector2i& mousePos)
{	
	if (border.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		currentState = ButtonState::HOVER;
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
			currentState = ButtonState::ACTIVE;
		}
	}
	else {
		currentState = ButtonState::IDLE;
	}

	changeColor();
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(border);
	target.draw(buttonText);
}

void Button::reset()
{
	currentState = ButtonState::IDLE;
	border.setFillColor(idleColor);
}

const bool Button::isButtonPressed() const
{
	return currentState == ButtonState::ACTIVE;
}

void Button::changeColor()
{
	switch (currentState) {
	case ButtonState::IDLE:
		border.setFillColor(idleColor);
		break;
	case ButtonState::HOVER:
		border.setFillColor(hoverColor);
		break;
	case ButtonState::ACTIVE:
		border.setFillColor(activeColor);
		break;
	default:
		border.setFillColor(idleColor);
		break;
	}
}
