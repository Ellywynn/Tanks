#include "../include/Tank.h"

Tank::Tank()
	:hp(100.f), rotationSpeed(10.f), armor(0.f)
{
	
}

Tank::~Tank()
{
}

void Tank::update(const float dt)
{

}

void Tank::render(sf::RenderTarget* target)
{
	target->draw(body);
	target->draw(head);
}