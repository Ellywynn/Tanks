#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State
{
private:
	void initKeybinds() override;
	void updateInput(const float dt);
public:
	MainMenuState(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys);
	~MainMenuState();

	void endState() override;
	void updateKeybinds(const float dt) override;
	void update(const float dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#endif