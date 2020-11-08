#include "../include/GameState.h"

GameState::GameState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	std::cout << "Game State\n";
	initKeybinds();
	loadAssets();
	initVariables();
	player = new Player(&mousePosView, &keybinds, &textures, &projectiles);
}

GameState::~GameState()
{
	for (auto& p : projectiles)
		delete p;
	delete player;
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
	std::string path = "assets/textures/Game/";
	textures.load(Textures::Game_PlayerBody, path + "player_body.png");
	textures.load(Textures::Game_PlayerHead, path + "player_head.png");
	textures.load(Textures::Game_StandartBullet, path + "standart_bullet.png");
}

void GameState::updateButtons()
{
}

void GameState::handleEvents()
{
	while (window->pollEvent(this->event)) {

	}
}

void GameState::initVariables()
{
	playerCamera.setSize(static_cast<sf::Vector2f>(window->getSize()));
	playerCamera.zoom(3.f);
	window->setView(playerCamera);
	showHitboxes = true;
}

void GameState::renderHitboxes()
{
	player->renderHitboxes(window);
	for (auto& p : projectiles)
		window->draw(p->hitbox.get());
}

void GameState::updateProjectiles(const float dt)
{
	for (auto& p : projectiles)
		p->update(dt);
}

void GameState::renderProjectiles()
{
	for (auto& p : projectiles)
		p->render(*window);
}

void GameState::updateView()
{
	playerCamera.setCenter(player->getPosition());
	window->setView(playerCamera);
}

void GameState::endState()
{
	window->setView(window->getDefaultView());
}

void GameState::update(const float dt)
{
	updateMousePositions();
	handleEvents();
	updateInput(dt);
	player->update(dt);
	updateView();
	updateProjectiles(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	player->render(window);
	renderProjectiles();
	if (showHitboxes)
		renderHitboxes();
}