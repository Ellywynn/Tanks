#include "../include/MainMenuState.h"

#include "../include/GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	initKeybinds();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initKeybinds()
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

void MainMenuState::updateInput(const float dt)
{
	quitState();	
}

void MainMenuState::endState()
{
	std::cout << "Ending state!\n";
}

void MainMenuState::updateKeybinds(const float dt)
{
	quitState();
}

void MainMenuState::update(const float dt)
{
	updateMousePositions();
	updateKeybinds(dt);
	updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	
}