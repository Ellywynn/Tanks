#include "EnemyTank.h"

EnemyTank::EnemyTank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles)
	:Tank(textures, projectiles)
{
	type = TankType::Enemy;
}

EnemyTank::~EnemyTank()
{
}
