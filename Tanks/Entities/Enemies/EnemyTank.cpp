#include "EnemyTank.h"

EnemyTank::EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles, Tank* player)
	:Tank(textures, projectiles)
{
	this->player = player;
	type = TankType::Enemy;

	rotateLeft = false;
	shooting = false;
	rotating = false;
}

EnemyTank::~EnemyTank()
{
}
