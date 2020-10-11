#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State
{
private:
	Entity player;

	void initKeybinds() override;
	void updateInput(const float dt);
public:
	GameState(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys);
	~GameState();

	void endState() override;
	void updateKeybinds(const float dt) override;
	void update(const float dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#endif