#include "../include/GameState.h"

GameState::GameState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	initKeybinds();
}

GameState::~GameState()
{
}

void GameState::initKeybinds()
{
	std::ifstream file("config/gamestate_keybinds.ini");

	if (file.is_open()) {
		std::string key = "";
		std::string value = "";
		while (file >> key >> value) {
			keybinds[key] = supportedKeys->at(value);
		}
	}
	else {
		std::cerr << "[ERROR]: Cannot open file gamestate_keybinds.ini\n";
	}

	file.close();
}

void GameState::updateInput(const float dt)
{
	quitState();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_UP"])))
		player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_LEFT"])))
		player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_DOWN"])))
		player.move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_RIGHT"])))
		player.move(dt, 1.f, 0.f);	
}

void GameState::endState()
{
	std::cout << "Ending state!\n";
}

void GameState::updateKeybinds(const float dt)
{
	quitState();
}

void GameState::update(const float dt)
{
	updateMousePositions();
	updateKeybinds(dt);
	updateInput(dt);
	player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	player.render(window);
}
