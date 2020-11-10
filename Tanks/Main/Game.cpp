#include "Game.h"

Game::Game()
{
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	delete window;

	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void Game::update()
{
	updateDt();
	if (!states.empty()) {
		states.top()->handleEvents();
		states.top()->update(dt);
		if (states.top()->getQuit()) {
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	else {
		window->close();
	}
}

void Game::render()
{
	window->clear();
	if (!states.empty())
		states.top()->render();
	window->display();
}

void Game::updateDt()
{
	// time it takes to handle one frame
	dt = dtClock.restart().asSeconds();
}

void Game::initWindow()
{
	// window config file
	std::ifstream wcfg("config/window.ini");

	sf::VideoMode window_size(800, 600);
	std::string window_title = "";
	uint32_t framerate = 60;
	bool vsync = false;
	bool fullscreen = false;

	if (wcfg.is_open()) {
		std::getline(wcfg, window_title);
		wcfg >> window_size.width >> window_size.height;
		wcfg >> framerate;
		wcfg >> vsync;
		wcfg >> fullscreen;
	}
	else {
		std::cerr << "[ERROR]: Cannot open file cfg/window.ini\n";
	}

	wcfg.close();

	window = new sf::RenderWindow(window_size, window_title,
		fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window->setFramerateLimit(framerate);
	window->setVerticalSyncEnabled(vsync);
}

void Game::initStates()
{
	states.push(new MainMenuState(window, &supportedKeys,&states));
}

void Game::initKeys()
{
	std::ifstream file("config/keys.ini");

	if (file.is_open()) {
		std::string key = "";
		int value = 0;
		while (file >> key >> value) {
			supportedKeys[key.c_str()] = value;
		}
	}
	else {
		std::cerr << "[ERROR]: Cannot open file keys.ini.\n";
	}

	file.close();
}
