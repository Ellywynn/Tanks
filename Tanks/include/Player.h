#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player : public Tank
{
public:
	Player(sf::Vector2f* mousePosition,
		std::unordered_map<std::string, int>* keybinds);
	~Player();

	sf::Vector2f* mousePosition;
	std::unordered_map<std::string, int>* keybinds;

	void update(const float dt) override;
	void render(sf::RenderTarget* target) override;
	void renderHitboxes(sf::RenderTarget* target);
	void updateInput(const float dt);
	void loadAssets(ResourceHolder<sf::Texture, Textures>* textures);

	const sf::Vector2f getPosition() const;
private:
	void rotate(const float dt, float dir);
	void move(const float dt, float dir) override;
	void moveHead();
	void moveBody(const float dt);

	Hitbox hb_body;
	Hitbox hb_head;
};

#endif