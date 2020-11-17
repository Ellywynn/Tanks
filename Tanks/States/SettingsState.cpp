#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states, SettingsContainer* gameSettings)
	:State(window, supportedKeys, states), settings(gameSettings)
{
	loadAssets();
	initVariables();
	initButtons();
}

SettingsState::~SettingsState()
{
	delete ddl_resolutions;
	delete sl_musicVol;
	delete sl_soundsVol;
	delete sl_framerate;
	delete cb_fullscreen;
	delete cb_vsynch;
}

void SettingsState::updateButtons()
{
	for (auto& b : buttons)
		b.second->update(event, mousePosWindow);

	if (buttons["Apply"]->isButtonPressed())
	{
		if (ddl_resolutions->isChanged())
		{
			window->create(ddl_resolutions->getActiveValue(), settings->title);
		}

		settings->resolution = ddl_resolutions->getActiveValue();
		settings->musicVolume = sl_musicVol->getValue();
		settings->soundsVolume = sl_soundsVol->getValue();

		settings->saveToFile();

		resolutions->resetChange();
		musicVol->resetChange();
		soundsVol->resetChange();
	}

	if (buttons["Exit"]->isButtonPressed())
	{
		if (!soundsVol->isChanged())
		{
			// set default value here
		}

		if (!musicVol->isChanged())
		{
			// set default value here
		}
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
	updateWidgets(dt);
	updateButtons();
}

void SettingsState::render(sf::RenderTarget* target)
{
	for (auto& b : buttons)
		b.second->render(*window);

	musicVol->render(window);
	soundsVol->render(window);
	resolutions->render(window);
	chbox->render(window);
}

void SettingsState::endState()
{
	resolutions->resetChange();
	musicVol->resetChange();
	soundsVol->resetChange();
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
	ddl_resolutions = new DropDownList<sf::VideoMode>(250.f, 30.f,
		650.f, 60.f, &fonts.get(Fonts::Arial));

	std::vector<sf::VideoMode> availableModes = sf::VideoMode::getFullscreenModes();
	for (size_t i = 0; i < availableModes.size(); i++)
	{
		ddl_resolutions->add(availableModes[i], std::to_string(availableModes[i].width)
			+ "x" + std::to_string(availableModes[i].height));
	}

	ddl_resolutions->setActiveValue(settings->resolution,
		std::to_string(settings->resolution.width) + "x" + std::to_string(settings->resolution.height));


	sl_musicVol = new Slider(250.f, 20.f, 150.f, 60.f, 0, 100, &mousePosWindow, "%", "Music");
	musicVol->setFont(&fonts.get(Fonts::Arial));
	musicVol->setValue(settings->musicVolume);

	soundsVol = new Slider(250.f, 20.f, 150.f, 130.f, 0, 100, &mousePosWindow, "%", "Sounds");
	soundsVol->setFont(&fonts.get(Fonts::Arial));
	soundsVol->setValue(settings->soundsVolume);

	chbox = new Checkbox(50.f, 500.f, 100.f, true);
}

void SettingsState::loadAssets()
{
	settings->loadFromFile();
	fonts.load(Fonts::Arial, "assets/fonts/arial.ttf");
}

void SettingsState::updateWidgets(const float dt)
{
	resolutions->update(dt, mousePosWindow, event);
	musicVol->update(dt);
	soundsVol->update(dt);
	chbox->update(dt, mousePosWindow);

	if (musicVol->isChanged())
	{
		// set new volume
	}

	if (soundsVol->isChanged())
	{
		// set new volume
	}

	if (musicVol->isChanged() || soundsVol->isChanged())
	{
		// set new volume right now
	}
}
