#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	loadAssets();
	initVariables();
	initButtons();
}

SettingsState::~SettingsState()
{
	delete resolutions;
	delete musicSlider;
}

void SettingsState::updateButtons()
{
	for (auto& b : buttons)
		b.second->update(event, mousePosWindow);

	if (buttons["Apply"]->isButtonPressed())
	{
		// apply settings
	}

	if (buttons["Exit"]->isButtonPressed())
	{
		endState();
	}
}

void SettingsState::handleEvents()
{
	while (window->pollEvent(event))
	{

	}
}

void SettingsState::updateInput(const float dt)
{
}

void SettingsState::update(const float dt)
{
	updateMousePositions();
	musicSlider->update(dt);
	resolutions->update(dt, mousePosWindow, event);
	updateButtons();
}

void SettingsState::render(sf::RenderTarget* target)
{
	resolutions->render(window);
	musicSlider->render(window);

	for (auto& b : buttons)
		b.second->render(*window);
}

void SettingsState::endState()
{
	quit = true;
}

void SettingsState::initKeybinds()
{
}

void SettingsState::initButtons()
{
	buttons["Apply"] = new Button("Apply", 300.f, 500.f, &fonts.get(Fonts::Arial));
	buttons["Exit"] = new Button("Exit", 410.f, 500.f, &fonts.get(Fonts::Arial));
}

void SettingsState::initVariables()
{
	resolutions = new DropDownList<sf::VideoMode>(250.f, 30.f,
		150.f, 50.f, &fonts.get(Fonts::Arial));
	musicSlider = new Slider(250.f, 20.f, 150.f, 120.f, 0.f, 100.f, &mousePosWindow);

	std::vector<sf::VideoMode> availableModes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < availableModes.size(); i++)
	{
		resolutions->add(availableModes[i], std::to_string(availableModes[i].width)
			+ "x" + std::to_string(availableModes[i].height));
	}
}

void SettingsState::loadAssets()
{
	fonts.load(Fonts::Arial, "assets/fonts/arial.ttf");
}