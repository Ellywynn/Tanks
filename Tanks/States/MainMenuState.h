#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	~MainMenuState();

	void endState() override;
	void handleEvents() override;
	void update(const float dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
private:
	DropDownList<float>* ddl;

	// Update functions
	void updateButtons() override;
	void updateInput(const float dt) override;
	
	// Init functions
	void initKeybinds() override;
	void initButtons() override;
	void initVariables() override;
	void initSprites();
	void loadAssets() override;
	void loadTextures();
	void loadSounds();
	void loadFonts();
	
	void quitState() override;
	void pushGameState();

	sf::Sprite createSprite(sf::Texture& texture);
private:
	std::unordered_map<std::string, Button*> buttons;
};

#endif