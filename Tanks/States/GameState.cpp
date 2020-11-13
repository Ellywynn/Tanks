#include "GameState.h"

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
	enemies.push_back(new EnemyLittleTank(&textures, &projectiles, player));
}

GameState::~GameState()
{
	for (auto& p : projectiles)
		delete p;
	delete player;

	for (auto& e : enemies)
		delete e;
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
	//textures.load(Textures::Game_EnemyLT_Head, path + "enemy_lt_head.png");
	//textures.load(Textures::Game_EnemyLT_Body, path + "enemy_lt_body.png");
}

void GameState::updateButtons()
{
}

void GameState::handleEvents()
{
	while (window->pollEvent(this->event)) {

	}
}

void GameState::checkCollisions()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if(projectiles[i]->hitbox.collides(target))
		{
			std::cout << "Collision detected!\n";
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
}

void GameState::initVariables()
{
	playerCamera.setSize(static_cast<sf::Vector2f>(window->getSize()));
	playerCamera.zoom(3.f);
	window->setView(playerCamera);
	showHitboxes = true;

	target.setSize(150.f, 150.f);
	target.setPosition(200.f, 200.f);
	target.setColor(sf::Color::Green);
	target.setRotation(30.f);
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
	for (auto& e : enemies)
		e->update(dt);
	updateView();
	updateProjectiles(dt);
	checkCollisions();
}

void GameState::render(sf::RenderTarget* target)
{
	player->render(window);
	renderProjectiles();
	for (auto& e : enemies)
		e->render(window);
	window->draw(this->target.get());
	if (showHitboxes)
		renderHitboxes();
}