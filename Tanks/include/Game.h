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

	// Initialization functions
	void initWindow();
	void initStates();
	void initKeys();
private:
	sf::RenderWindow *window;		// Game window
	std::stack<State*> states;		// Game states

	sf::Clock dtClock;				// Game clock
	float dt;						// Delta time

	// Allowed keys
	std::unordered_map<std::string, int> supportedKeys;
};

#endif