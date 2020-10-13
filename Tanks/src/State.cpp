#include "../include/State.h"

State::State(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	quit = false;
}

State::~State()
{
}

const bool State::getQuit() const
{
	return quit;
}

void State::quitState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["CLOSE"]))) {
		quit = true;
	}
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}
