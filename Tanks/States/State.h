#ifndef STATE_H
#define STATE_H

#include "../Entities/Entity.h"
#include "../GUI/GUI.h"
#include "../Utils/SettingsContainer.h"

enum class Textures
{
	MainMenu_Background = 0,

	Game_PlayerHead,
	Game_PlayerBody,
	Game_EnemyLT_Head,
	Game_EnemyLT_Body,

	Game_StandartBullet
};

enum class Sounds
{

};

enum class Fonts
{
	Arial = 0
};


class State
{
protected:
	// We need a pointer to the states stack to switch state
	std::stack<State*>* states;
	// This pointer is needed to render the state stuff
	sf::RenderWindow* window;

	// Keys
	std::unordered_map<std::string, int>* supportedKeys;
	std::unordered_map<std::string, int> keybinds;
	// Needed to quit the state
	bool quit;

	sf::Event event;

	// Mouse positions
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	ResourceHolder<sf::Texture, Textures> textures;
	ResourceHolder<sf::Sound, Sounds> sound;
	ResourceHolder<sf::Font, Fonts> fonts;

	std::unordered_map<std::string, sf::Sprite> sprites;

	// Init functions
	virtual void initKeybinds() = 0;
	virtual void initButtons() = 0;
	virtual void initVariables() = 0;
	virtual void loadAssets() = 0;
public:
	State(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~State();

	// Update functions
	virtual void updateMousePositions();
	virtual void updateButtons() = 0;
	virtual void handleEvents() = 0;
	virtual void updateInput(const float dt) = 0;
	virtual void update(const float dt) = 0;

	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	// Ending the state
	virtual void quitState();
	virtual void endState() = 0;
	const bool getQuit() const;
};

#endif