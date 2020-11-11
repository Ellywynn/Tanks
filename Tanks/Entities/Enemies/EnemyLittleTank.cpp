#include "EnemyLittleTank.h"

EnemyLittleTank::EnemyLittleTank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles, Tank* player)
	:EnemyTank(textures, projectiles, player)
{
	//head.setTexture(textures->get(Textures::Game_EnemyLT_Head));
	//body.setTexture(textures->get(Textures::Game_EnemyLT_Body));
	hb_body.setSize(head.getGlobalBounds().width,
		head.getGlobalBounds().height);
	hb_body.setSize(body.getGlobalBounds().width,
		body.getGlobalBounds().height);

	hp = 1000.f;
	armor = 0.1f; // 10%
	damage = 200.f;
	rotationSpeed = 50.f;
	attackSpeed = sf::seconds(1.f);
}

EnemyLittleTank::~EnemyLittleTank()
{
}

void EnemyLittleTank::update(const float dt)
{
	// rotating
	if (rotating)
	{
		if (rotateLeft) body.rotate(-rotationSpeed);
		else body.rotate(rotationSpeed);
	}
	else
	{
		
	}
}

void EnemyLittleTank::shoot(const sf::Vector2f& velocity)
{

}
