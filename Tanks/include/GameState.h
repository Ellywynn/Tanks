#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	~GameState();

	void endState() override;
	void update(const float dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
private:
	Player* player;
	sf::View playerCamera;

	std::vector<Projectile*> projectiles;

	bool showHitboxes;

	void initKeybinds() override;
	void updateInput(const float dt) override;
	void initButtons() override;
	void loadAssets() override;
	void updateButtons() override;
	void handleEvents() override;
	void initVariables() override;
	void renderHitboxes();
	void updateProjectiles(const float dt);
	void renderProjectiles();

	void updateView();
};

#endif