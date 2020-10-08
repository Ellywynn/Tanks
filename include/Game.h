#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <cstdint>

class Game
{
public:
	Game(uint32_t width = 800, uint32_t height = 600);
	~Game();
	void run();
private:
	void handleInput();
	void update();
	void render();

	void updateDt();
private:
	sf::RenderWindow window;
	sf::RectangleShape shape;

	sf::Clock dtClock;
	float dt;
};

#endif