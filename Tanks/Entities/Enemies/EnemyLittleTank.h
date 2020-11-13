#ifndef ENEMYLITTLETANK_H
#define ENEMYLITTLETANK_H

#include "EnemyTank.h"

class EnemyLittleTank : public EnemyTank
{
public:
	EnemyLittleTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles, Player* player);
	~EnemyLittleTank();

	void update(const float dt) override;
	void render(sf::RenderTarget* target) override;

	void shoot(const sf::Vector2f& velocity) override;
	void rotateBody(const float dt) override;
	void rotateHead(const float dt) override;
	
	void move(const float dt) override;
};

#endif