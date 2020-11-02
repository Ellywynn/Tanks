#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player : public Tank
{
public:
	Player(sf::Vector2i* mousePosition,
		std::unordered_map<std::string, int>* keybinds);
	~Player();

	sf::Vector2i* mousePosition;
	std::unordered_map<std::string, int>* keybinds;

	void update(const float dt) override;
	void render(sf::RenderTarget* target) override;
	void updateInput(const float dt);
	void loadAssets(ResourceHolder<sf::Texture, Textures>* textures);
private:
	void rotate(const float dt, float dir);
	void move(const float dt, float dir) override;
};

#endif