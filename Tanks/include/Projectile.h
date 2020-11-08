#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

// For collision cheching
enum class ProjectileType
{
	Player = 0,
	Enemy
};

class Projectile : public Entity
{
public:
	Projectile(ProjectileType type);
	virtual ~Projectile();

	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget& target);

	ProjectileType type;
	float damage;
	Hitbox hitbox;
	sf::Vector2f direction; // Flying direction
};

#endif