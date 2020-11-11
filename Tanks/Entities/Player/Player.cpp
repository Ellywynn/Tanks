#include "Player.h"

Player::Player(sf::Vector2f* mousePosition,
	std::unordered_map<std::string, int>* keybinds,
	ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles)
{
	this->mousePosition = mousePosition;
	this->keybinds = keybinds;
	this->textures = textures;
	this->projectiles = projectiles;

	tank = new PlayerTier1Tank(textures, projectiles);
}

Player::~Player()
{
	delete tank;
}

void Player::update(const float dt)
{
	updateInput(dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(tank->body);
	target->draw(tank->head);
}

void Player::renderHitboxes(sf::RenderTarget* target)
{
	target->draw(tank->hb_body.get());
	target->draw(tank->hb_head.get());
	
}

void Player::rotateBody(const float dt, float dir)
{
	// Get the next angle by adding rotation speed to the current angle
	// Set it to the hitbox and body itself
	float angle = tank->body.getRotation() + tank->rotationSpeed * dir * dt;
	tank->body.setRotation(angle);
	tank->hb_body.setRotation(tank->body.getRotation());

	// 1. Get hitbox rotation
	// 2. Get hitbox proper position
	// 3. Set it
	float x = std::cos(tank->body.getRotation() * 3.1415f / 180.f);
	float y = std::sin(tank->body.getRotation() * 3.1415f / 180.f);
	sf::Vector2f pos(x * 45.f - y * 14.f, y * 45.f + x * 14.f);
	tank->hb_body.setPosition(tank->body.getPosition() + pos);
}

void Player::move(const float dt, float dir)
{
	// 1. Get the angle rotation in rads
	// 2. Get the direction vector(cosx,sinx)
	// 3. Get the proper velocity
	sf::Vector2f playerPos = tank->body.getPosition();
	float angleRad = (tank->body.getRotation() + 180.f) * 3.1415f / 180.f;
	sf::Vector2f directionVector(std::cos(angleRad), std::sin(angleRad));
	sf::Vector2f velocity(directionVector * tank->getSpeed() * dt * dir);

	// 4. Set it to the player objects
	tank->head.move(velocity);
	tank->body.move(velocity);
	tank->hb_body.move(velocity);
	tank->hb_head.move(velocity);
}

void Player::moveHead()
{
	// Get the player position and direction vector from head to mouse
	sf::Vector2f playerPos = tank->body.getPosition();
	sf::Vector2f aimDir = static_cast<sf::Vector2f>(*mousePosition) - playerPos;

	// Get angle rotationg in rads and set it
	float angleDeg = 180.f / 3.1415 * atan2(aimDir.y, aimDir.x);
	tank->head.setRotation(angleDeg - 180.f);
	tank->hb_head.setRotation(tank->head.getRotation());

	// 1. Get the angle rotation
	// 2. Set hitbox position correctly
	float ang = atan2(aimDir.y, aimDir.x);
	float x = std::cos(ang);
	float y = std::sin(ang);
	sf::Vector2f pos(x * 155.f + y * 15.f, y * 155.f - x * 15.f);
	tank->hb_head.setPosition(tank->head.getPosition() + pos);
}

void Player::moveBody(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_UP"))))
		move(dt, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_DOWN"))))
		move(dt, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_LEFT"))))
		rotateBody(dt, -1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_RIGHT"))))
		rotateBody(dt, 1);
}

void Player::shoot()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (tank->canShoot())
		{
			sf::Vector2f playerPos = tank->body.getPosition();
			sf::Vector2f aimDir = static_cast<sf::Vector2f>(*mousePosition) - playerPos;
			float vector_lenght = sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));
			sf::Vector2f velocity(aimDir.x / vector_lenght,
				aimDir.y / vector_lenght);

			tank->shoot(velocity);
		}
	}
}

void Player::updateInput(const float dt)
{
	moveHead();
	moveBody(dt);
	shoot();
}

const sf::Vector2f Player::getPosition() const
{
	return tank->body.getPosition();
}

const Tank* Player::getTank() const
{
	return tank;
}
