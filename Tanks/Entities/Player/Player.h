#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerTier1Tank.h"
		
class Player : public Entity
{
public:
	Player(sf::Vector2f* mousePosition,
		std::unordered_map<std::string, int>* keybinds,
		ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles);
	~Player();

	sf::Vector2f* mousePosition;						// Cursor position for tank head		
	std::unordered_map<std::string, int>* keybinds;		// Controls
	ResourceHolder<sf::Texture, Textures>* textures;
	std::vector<Projectile*>* projectiles;

	void update(const float dt);
	void updateInput(const float dt);

	void render(sf::RenderTarget* target);
	void renderHitboxes(sf::RenderTarget* target);

	const sf::Vector2f getPosition() const override;
	const Tank* getTank() const;
private:
	void move(const float dt, float dir);
	void moveHead();
	void moveBody(const float dt);
	
	void rotateBody(const float dt, float dir);
	void shoot();

	Tank* tank;											// Player current tank
};

#endif