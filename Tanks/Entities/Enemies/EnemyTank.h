#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "../Tank.h"
#include "../Player/Player.h"
#include <cmath>

class EnemyTank : public Tank 
{
public:
	EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
		std::vector<Projectile*>* projectiles, Player* player);
	virtual ~EnemyTank();

	virtual void update(const float dt) = 0;
	virtual void rotateBody(const float dt) = 0;
	virtual void rotateHead(const float dt) = 0;
	virtual void move(const float dt) = 0;

	Player* player;

	float headRotationSpeed;
	
	bool moveForward;
	sf::Time moveTime;
	sf::Clock moveTimer;

	sf::Time waitForMoveTime;
	sf::Clock waitForMoveTimer;

	bool shooting;
	bool rotateLeft;
	
	bool rotating;
	sf::Time waitForRotate;
	sf::Clock rotWaitingTimer;
	
	sf::Time rotationTime;
	sf::Clock rotationTimer;
};

#endif