#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
protected:
	sf::RenderWindow* window;
	std::unordered_map<std::string, int>* supportedKeys;
	std::unordered_map<std::string, int> keybinds;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::vector<sf::Texture> textures;

	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool getQuit() const;

	virtual void quitState();

	virtual void updateMousePositions();
	virtual void endState() = 0;
	virtual void updateKeybinds(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif