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
	void initKeybinds() override;
	void initButtons() override;
	void updateButtons() override;
	void updateInput(const float dt) override;
	void quitState() override;

	void loadAssets() override;
	void loadTextures();
	void loadSounds();
	void loadFonts();
	void initSprites();

	void pushGameState();

	sf::Sprite createSprite(sf::Texture& texture);
private:
	std::unordered_map<std::string, std::unique_ptr<Button>> buttons;
};

#endif