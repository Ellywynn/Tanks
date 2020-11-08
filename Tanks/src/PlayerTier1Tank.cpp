#include "../include/PlayerTier1Tank.h"

PlayerTier1Tank::PlayerTier1Tank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles)
	:Tank(textures, projectiles)
{
	type = TankType::Player;
	attackSpeed = sf::seconds(1.f);
	rotationSpeed = 90.f;
	movementSpeed = 100.f;

	// Get and set textures
	head.setTexture(textures->get(Textures::Game_PlayerHead));
	body.setTexture(textures->get(Textures::Game_PlayerBody));

	// Origins in the center
	head.setOrigin(head.getGlobalBounds().width / 2.f,
		head.getGlobalBounds().height / 2.f);
	body.setOrigin(body.getGlobalBounds().width / 2.f,
	body.getGlobalBounds().height / 2.f);

	// Spawn position
	head.setPosition(500.f, 500.f);
	body.setPosition(500.f, 500.f);

	hb_body.setSize(320.f, 170.f);
	hb_head.setSize(190.f, 30.f);

	hb_body.setPosition(body.getPosition().x + 45.f,
		body.getPosition().y + 14.f);

	hb_head.setColor(sf::Color::Yellow);
}

PlayerTier1Tank::~PlayerTier1Tank()
{
}

void PlayerTier1Tank::shoot(const sf::Vector2f& velocity)
{
	projectiles->push_back(new StandartBullet(ProjectileType::Player,
		textures->get(Textures::Game_StandartBullet), hb_head.getPosition(),
		velocity, head.getRotation()));

	restartClock();
}