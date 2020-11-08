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

	bool showHitboxes;		// For debug				

	// Update functions
	void updateInput(const float dt) override;
	void updateButtons() override;
	void updateProjectiles(const float dt);
	void updateView();
	void handleEvents() override;
	
	// Render functions
	void renderHitboxes();
	void renderProjectiles();
	
	// Init functions
	void initKeybinds() override;
	void initButtons() override;
	void initVariables() override;
	void loadAssets() override;
};

#endif