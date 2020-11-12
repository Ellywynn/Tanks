#include "EnemyTank.h"

EnemyTank::EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles, Player* player)
	:Tank(textures, projectiles)
{
	this->player = player;
	type = TankType::Enemy;

	rotateLeft = false;
	shooting = false;
	rotating = false;
	moveForward = true;
	moveTime = sf::seconds(static_cast<float>(std::rand() % 5 + 2));
	waitForMoveTime = sf::seconds(static_cast<float>(std::rand() % 5 + 2));
	waitForRotate = sf::seconds(static_cast<float>(std::rand() % 6 + 1)); // 1-5
	rotationTime = sf::seconds(static_cast<float>(std::rand() % 4 + 1));  // 1-2
}

EnemyTank::~EnemyTank()
{
}