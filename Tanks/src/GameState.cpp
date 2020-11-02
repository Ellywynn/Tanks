#include "../include/GameState.h"

GameState::GameState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states),
	player(&mousePosWindow, &keybinds)
{
	initKeybinds();
	loadAssets();
	player.loadAssets(&textures);
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
}

void GameState::initButtons()
{
}

void GameState::loadAssets()
{
	textures.load(Textures::Game_PlayerBody, "assets/textures/Game/player_body.png");
	textures.load(Textures::Game_PlayerHead, "assets/textures/Game/player_head.png");
}

void GameState::updateButtons()
{
}

void GameState::handleEvents()
{
	while (window->pollEvent(this->event)) {

	}
}

void GameState::endState()
{
	
}

void GameState::update(const float dt)
{
	updateMousePositions();
	handleEvents();
	updateInput(dt);
	player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	player.render(window);
}