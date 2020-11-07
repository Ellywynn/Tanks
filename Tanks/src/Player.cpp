#include "../include/Player.h"

Player::Player(sf::Vector2f* mousePosition,
	std::unordered_map<std::string, int>* keybinds)
{
	this->mousePosition = mousePosition;
	this->keybinds = keybinds;

	type = TankType::Player;
	attackSpeed = sf::seconds(1.f);
	rotationSpeed = 90.f;
	movementSpeed = 100.f;
}

Player::~Player()
{
}

void Player::update(const float dt)
{
	updateInput(dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(body);
	target->draw(head);
}

void Player::renderHitboxes(sf::RenderTarget* target)
{
	target->draw(hb_body.get());
	target->draw(hb_head.get());
}

void Player::rotate(const float dt, float dir)
{
	float angle = body.getRotation() + rotationSpeed * dir * dt;
	body.setRotation(angle);
	hb_body.setRotation(body.getRotation());

	float x = std::cos(body.getRotation() * 3.1415f / 180.f);
	float y = std::sin(body.getRotation() * 3.1415f / 180.f);
	sf::Vector2f pos(x * 45.f - y * 14.f, y * 45.f + x * 14.f);
	hb_body.setPosition(body.getPosition() + pos);
}

void Player::move(const float dt, float dir)
{
	sf::Vector2f playerPos = body.getPosition();
	float angleRad = (body.getRotation() + 180.f) * 3.1415f / 180.f;
	sf::Vector2f directionVector(std::cos(angleRad), std::sin(angleRad));
	sf::Vector2f velocity(directionVector * movementSpeed * dt * dir);

	head.move(velocity);
	body.move(velocity);
	hb_body.move(velocity);
	hb_head.move(velocity);
}

void Player::moveHead()
{
	sf::Vector2f playerPos = body.getPosition();
	sf::Vector2f aimDir = static_cast<sf::Vector2f>(*mousePosition) - playerPos;

	float angleDeg = 180 / 3.1415 * atan2(aimDir.y, aimDir.x);
	head.setRotation(angleDeg - 180.f);
	hb_head.setRotation(head.getRotation());

	float ang = atan2(aimDir.y, aimDir.x);
	float x = std::cos(ang);
	float y = std::sin(ang);
	sf::Vector2f pos(x * 155.f + y * 15.f, y * 155.f - x * 15.f);
	hb_head.setPosition(head.getPosition() + pos);
}

void Player::moveBody(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_UP"))))
		move(dt, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_DOWN"))))
		move(dt, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_LEFT"))))
		rotate(dt, -1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_RIGHT"))))
		rotate(dt, 1);
}

void Player::updateInput(const float dt)
{
	moveHead();
	moveBody(dt);
}

void Player::loadAssets(ResourceHolder<sf::Texture, Textures>* textures)
{
	head.setTexture(textures->get(Textures::Game_PlayerHead));
	body.setTexture(textures->get(Textures::Game_PlayerBody));

	head.setOrigin(head.getGlobalBounds().width / 2.f,
		head.getGlobalBounds().height / 2.f);
	body.setOrigin(body.getGlobalBounds().width / 2.f,
		body.getGlobalBounds().height / 2.f);

	head.setPosition(500.f, 500.f);
	body.setPosition(500.f, 500.f);

	hb_body.setSize(320.f, 170.f);
	hb_head.setSize(190.f, 30.f);
	hb_body.setPosition(body.getPosition().x + 45.f,
		body.getPosition().y + 14.f);

	hb_head.setColor(sf::Color::Yellow);
}

const sf::Vector2f Player::getPosition() const
{
	return body.getPosition();
}