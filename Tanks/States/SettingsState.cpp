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

		ddl_resolutions->resetChange();
		sl_musicVol->resetChange();
		sl_soundsVol->resetChange();
	}

	if (buttons["Exit"]->isButtonPressed())
	{
		if (!sl_soundsVol->isChanged())
		{
			// set default value here
		}

		if (!sl_musicVol->isChanged())
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
	window->draw(background);
	for (auto& b : buttons)
		b.second->render(*window);

	for (auto& t : settingsTexts)
		window->draw(t);
	window->draw(musicText);
	window->draw(soundsText);

	sl_musicVol->render(window);
	sl_soundsVol->render(window);
	ddl_resolutions->render(window);
	cb_fullscreen->render(window);
	cb_vsynch->render(window);
}

void SettingsState::endState()
{
	ddl_resolutions->resetChange();
	sl_musicVol->resetChange();
	sl_soundsVol->resetChange();
	cb_fullscreen->resetChange();
	cb_vsynch->resetChange();

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
	sf::Font& arial = fonts.get(Fonts::Arial);

	background.setSize(sf::Vector2f(window->getSize().x * 0.8f,
		window->getSize().y * 0.8f));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
	background.setFillColor(sf::Color(0, 0, 0, 200));

	settingsTexts[0].setString("Resolution");
	settingsTexts[1].setString("Max FPS");
	settingsTexts[2].setString("Fullscreen");
	settingsTexts[3].setString("VSynch");

	musicText.setString("Music");
	soundsText.setString("Sounds");
	musicText.setFont(arial);
	soundsText.setFont(arial);
	musicText.setCharacterSize(16u);
	soundsText.setCharacterSize(16u);

	musicText.setPosition(
		background.getPosition().x - background.getGlobalBounds().width / 2.f
		+ 20.f - musicText.getGlobalBounds().width,
		background.getPosition().y - background.getOrigin().y
		+ 20.f);

	soundsText.setPosition(
		background.getPosition().x - background.getGlobalBounds().width / 2.f
		+ 20.f - soundsText.getGlobalBounds().width,
		background.getPosition().y - background.getOrigin().y
		+ 20.f);

	for (int i = 1; i <= settingsTexts.size(); i++)
	{
		settingsTexts[i - 1].setFont(arial);
		settingsTexts[i - 1].setCharacterSize(16u);
		settingsTexts[i - 1].setPosition(
			background.getPosition().x - background.getOrigin().x + 20.f,
			background.getPosition().y - background.getOrigin().y
			+ 20.f + i * settingsTexts[i - 1].getGlobalBounds().height);
	}

	ddl_resolutions = new DropDownList<sf::VideoMode>(250.f, 30.f,
		settingsTexts[0].getPosition().x + settingsTexts[0].getGlobalBounds().width + 10.f,
		settingsTexts[0].getPosition().y, &fonts.get(Fonts::Arial));

	std::vector<sf::VideoMode> availableModes = sf::VideoMode::getFullscreenModes();
	for (size_t i = 0; i < availableModes.size(); i++)
	{
		ddl_resolutions->add(availableModes[i], std::to_string(availableModes[i].width)
			+ "x" + std::to_string(availableModes[i].height));
	}

	ddl_resolutions->setActiveValue(settings->resolution,
		std::to_string(settings->resolution.width) + "x" + std::to_string(settings->resolution.height));

	sl_framerate = new Slider(250.f, 20.f,
		settingsTexts[1].getPosition().x + settingsTexts[1].getGlobalBounds().width + 10.f,
		settingsTexts[1].getPosition().y, 20, 240, &mousePosWindow);
	sl_framerate->setFont(&fonts.get(Fonts::Arial));
	sl_framerate->setValue(settings->framerate);

	cb_fullscreen = new Checkbox(40.f, settingsTexts[2].getPosition().x + settingsTexts[2].getGlobalBounds().width + 10.f,
		settingsTexts[2].getPosition().y, settings->fullscreen);

	cb_vsynch = new Checkbox(40.f, settingsTexts[3].getPosition().x + settingsTexts[3].getGlobalBounds().width + 10.f,
		settingsTexts[3].getPosition().y, settings->vsynch);

	sl_musicVol = new Slider(250.f, 20.f,
		musicText.getPosition().x + musicText.getGlobalBounds().width + 10.f,
		musicText.getPosition().y, 0, 100, &mousePosWindow, "%");
	sl_musicVol->setFont(&fonts.get(Fonts::Arial));
	sl_musicVol->setValue(settings->musicVolume);

	sl_soundsVol = new Slider(250.f, 20.f,
		soundsText.getPosition().x + soundsText.getGlobalBounds().width + 10.f,
		soundsText.getPosition().y, 0, 100, &mousePosWindow, "%");
	sl_soundsVol->setFont(&fonts.get(Fonts::Arial));
	sl_soundsVol->setValue(settings->soundsVolume);
}

void SettingsState::loadAssets()
{
	settings->loadFromFile();
	fonts.load(Fonts::Arial, "assets/fonts/arial.ttf");
}

void SettingsState::updateWidgets(const float dt)
{
	ddl_resolutions->update(dt, mousePosWindow, event);
	sl_musicVol->update(dt);
	sl_soundsVol->update(dt);
	cb_fullscreen->update(dt, mousePosWindow);
	cb_vsynch->update(dt, mousePosWindow);

	if (sl_musicVol->isChanged())
	{
		// set new volume
	}

	if (sl_soundsVol->isChanged())
	{
		// set new volume
	}

	if (sl_musicVol->isChanged() || sl_soundsVol->isChanged())
	{
		// set new volume right now
	}
}
