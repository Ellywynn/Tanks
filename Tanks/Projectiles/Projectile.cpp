#include "Projectile.h"

Projectile::Projectile(ProjectileType type)
{
}

Projectile::~Projectile()
{
}

void Projectile::render(sf::RenderTarget& target)
{
	if(sprite != nullptr)
		target.draw(*sprite);
}
