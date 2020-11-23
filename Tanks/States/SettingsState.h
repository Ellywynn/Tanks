#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "../Utils/SettingsContainer.h"
#include <array>

class SettingsState : public State
{
public:
	SettingsState(sf::RenderWindow* window,
		std::unordered_map<std::string, int>* supportedKeys,
		std::stack<State*>* states, SettingsContainer* gameSettings);
	~SettingsState();

	void updateButtons() override;
	void handleEvents() override;
	void updateInput(const float dt) override;
	void update(const float dt) override;

	void render(sf::RenderTarget* target) override;

	void endState() override;

	void initKeybinds()  override;
	void initButtons() 	 override;
	void initVariables() override;
	void loadAssets()    override;
private:
	void updateWidgets(const float dt);
	void initElements();
private:
	std::unordered_map<std::string, Button*> buttons;

	SettingsContainer* settings;

	Slider* sl_musicVol;
	Slider* sl_soundsVol;
	Slider* sl_framerate;
	Checkbox* cb_fullscreen;
	Checkbox* cb_vsynch;
	DropDownList<sf::VideoMode>* ddl_resolutions;

	sf::RectangleShape background;

	// left side texts
	std::array<sf::Text, 4> settingsTexts;

	sf::Text musicText;
	sf::Text soundsText;
};

#endif