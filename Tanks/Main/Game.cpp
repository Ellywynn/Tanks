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
	window->clear(sf::Color(150,150,150));
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
	settings.loadFromFile();

	window = new sf::RenderWindow(settings.resolution, settings.title,
		settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window->setFramerateLimit(settings.framerate);
	window->setVerticalSyncEnabled(settings.vsynch);
}

void Game::initStates()
{
	//states.push(new MainMenuState(window, &supportedKeys,&states));
	states.push(new SettingsState(window, &supportedKeys, &states, &settings));
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
