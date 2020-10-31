#ifndef STATE_H
#define STATE_H

#include "Entity.h"
#include "Button.h"

enum class Textures;
enum class Sounds;
enum class Fonts;

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::unordered_map<std::string, int>* supportedKeys;
	std::unordered_map<std::string, int> keybinds;
	bool quit;

	sf::Event event;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	ResourceHolder<sf::Texture, Textures> textures;
	ResourceHolder<sf::Sound, Sounds> sound;
	ResourceHolder<sf::Font, Fonts> fonts;

	std::unordered_map<std::string, sf::Sprite> sprites;

	virtual void initKeybinds() = 0;
	virtual void initButtons() = 0;
	virtual void loadAssets() = 0;
public:
	State(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~State();

	const bool getQuit() const;

	virtual void quitState();

	virtual void updateMousePositions();
	virtual void endState() = 0;
	virtual void updateButtons() = 0;
	virtual void handleEvents() = 0;
	virtual void updateInput(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif