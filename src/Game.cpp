#include "../include/Game.h"

Game::Game(uint32_t width, uint32_t height)
	:window(sf::VideoMode(width, height), "Window Title")
{
	this->shape.setSize(sf::Vector2f(width / 2.f, height / 2.f));
	this->shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
	this->shape.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	this->shape.setFillColor(sf::Color::Green);
}

Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		render();
	}
}

void Game::handleInput()
{
	sf::Event ev;
	while (window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	handleInput();
	updateDt();
}

void Game::render()
{
	window.clear();
	window.draw(shape);
	window.display();
}

void Game::updateDt()
{
	// time it takes to handle one frame
	dt = dtClock.restart().asSeconds();
}
