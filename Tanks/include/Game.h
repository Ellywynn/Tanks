#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void update();
	void render();

	void updateDt();

	void initWindow();
	void initStates();
	void initKeys();
private:
	sf::RenderWindow *window;
	std::stack<State*> states;

	sf::Clock dtClock;
	float dt;

	std::unordered_map<std::string, int> supportedKeys;
};

#endif