#include "EnemyLittleTank.h"

EnemyLittleTank::EnemyLittleTank(ResourceHolder<sf::Texture, Textures>* textures,
	std::vector<Projectile*>* projectiles, Player* player)
	:EnemyTank(textures, projectiles, player)
{
	//head.setTexture(textures->get(Textures::Game_EnemyLT_Head));
	//body.setTexture(textures->get(Textures::Game_EnemyLT_Body));
	head.setTexture(textures->get(Textures::Game_PlayerHead));
	body.setTexture(textures->get(Textures::Game_PlayerBody));
	hb_body.setSize(head.getGlobalBounds().width,
		head.getGlobalBounds().height);
	hb_body.setSize(body.getGlobalBounds().width,
		body.getGlobalBounds().height);

	head.setOrigin(head.getGlobalBounds().width / 2.f,
		head.getGlobalBounds().height / 2.f);
	body.setOrigin(body.getGlobalBounds().width / 2.f,
		body.getGlobalBounds().height / 2.f);

	head.setPosition(-300.f, -300.f);
	body.setPosition(-300.f, -300.f);

	movementSpeed = 100.f;
	headRotationSpeed = 30.f;
	hp = 1000.f;
	armor = 0.1f; // 10%
	damage = 200.f;
	rotationSpeed = 50.f;
	attackSpeed = sf::seconds(1.f);

	attacked = false;
	triggerArea.setSize(sf::Vector2f(500.f, 500.f));
	triggerArea.setOrigin(triggerArea.getSize().x / 2.f,
		triggerArea.getSize().y / 2.f);
	triggerArea.setPosition(hb_body.getPosition());
}

EnemyLittleTank::~EnemyLittleTank()
{
}

void EnemyLittleTank::update(const float dt)
{
	rotateBody(dt);
	rotateHead(dt);
	move(dt);
}

void EnemyLittleTank::render(sf::RenderTarget* target)
{
	target->draw(body);
	target->draw(head);
	target->draw(triggerArea);
}

void EnemyLittleTank::shoot(const sf::Vector2f& velocity)
{
	projectiles->push_back(new StandartBullet(ProjectileType::Enemy,
		textures->get(Textures::Game_StandartBullet), hb_head.getPosition(),
		velocity, head.getRotation()));

	attackClock.restart();
}

void EnemyLittleTank::rotateBody(const float dt)
{
	if (rotating)
	{
		if (rotationTimer.getElapsedTime() <= rotationTime)
		{
			//std::cout << "ROTATING BODY\n";
			if (rotateLeft) body.rotate(-rotationSpeed * dt);
			else body.rotate(rotationSpeed * dt);
		}
		else
		{
			rotating = false;
			rotWaitingTimer.restart();
			waitForRotate = sf::seconds(static_cast<float>(std::rand() % 5 + 1)); // 1-5
		}
	}
	else
	{
		if (rotWaitingTimer.getElapsedTime() >= waitForRotate)
		{
			rotating = true;
			rotateLeft = std::rand() % 2;
			rotationTimer.restart();
			rotationTime = sf::seconds(static_cast<float>(std::rand() % 4 + 1));  // 1-2
		}
	}
}

void EnemyLittleTank::rotateHead(const float dt)
{
	if (attacked ||
		triggerArea.getGlobalBounds().intersects(player->getGlobalBounds()))
	{
		sf::Vector2f thisCenterPos(head.getPosition());
		sf::Vector2f lenDiff = player->getPosition() - thisCenterPos;

		float angle = std::atan2f(lenDiff.y, lenDiff.x) * (180.f / 3.1415f);
		float rspeed = headRotationSpeed * dt;

		float aMod = std::fmod(angle - head.getRotation(), 360.f);
		float aDiff = aMod < 0.f ? aMod + 180.f : aMod - 180.f;

		float newRotation = head.getRotation();

		if (aDiff < -rspeed) {
			newRotation -= rspeed;
		}
		else if (aDiff > rspeed) {
			newRotation += rspeed;
		}
		else {
			aDiff = 0.f;
			newRotation = angle - 180.f;
		}
		head.setRotation(newRotation);
	}
}

void EnemyLittleTank::move(const float dt)
{
	if (waitForMoveTimer.getElapsedTime() >= waitForMoveTime)
	{
		if (moveTimer.getElapsedTime() <= moveTime)
		{
			float angleRad = (body.getRotation() + 180.f) * 3.1415f / 180.f;
			sf::Vector2f directionVector(std::cos(angleRad), std::sin(angleRad));
			sf::Vector2f velocity(directionVector * getSpeed() * dt);
			if (!moveForward) velocity = sf::Vector2f(velocity.x * -1.f, velocity.y * -1.f);

			// 4. Set it to the player objects
			head.move(velocity);
			body.move(velocity);
			hb_body.move(velocity);
			hb_head.move(velocity);
			triggerArea.move(velocity);
		}
		else
		{
			waitForMoveTimer.restart();
			moveTime = sf::seconds(static_cast<float>(std::rand() % 5 + 2));
			waitForMoveTime = sf::seconds(static_cast<float>(std::rand() % 5 + 2));
			moveForward = static_cast<float>(std::rand() % 2);
		}
	}
	else
	{
		moveTimer.restart();
	}
}
