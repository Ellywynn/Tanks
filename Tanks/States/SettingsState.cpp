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

	for (auto& b : buttons)
		delete b.second;
}

void SettingsState::updateButtons()
{
	for (auto& b : buttons)
		b.second->update(event, mousePosWindow);

	if (buttons["Apply"]->isButtonPressed())
	{
		settings->resolution = ddl_resolutions->getActiveValue();
		settings->musicVolume = sl_musicVol->getValue();
		settings->soundsVolume = sl_soundsVol->getValue();
		settings->framerate = sl_framerate->getValue();
		settings->fullscreen = cb_fullscreen->isSelected();
		settings->vsynch = cb_vsynch->isSelected();

		settings->saveToFile();

		if (ddl_resolutions->isChanged())
		{
			window->create(ddl_resolutions->getActiveValue(), settings->title,
				settings->fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
			window->setFramerateLimit(settings->framerate);
			delete ddl_resolutions;
			delete sl_musicVol;
			delete sl_framerate;
			delete sl_soundsVol;
			delete cb_fullscreen;
			delete cb_vsynch;
			delete buttons["Apply"];
			delete buttons["Exit"];

			initVariables();
			initButtons();
		}
		else if (cb_fullscreen->isChanged())
		{
			window->create(ddl_resolutions->getActiveValue(), settings->title,
				settings->fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
			window->setFramerateLimit(settings->framerate);
		}

		ddl_resolutions->resetChange();
		sl_framerate->resetChange();
		sl_musicVol->resetChange();
		sl_soundsVol->resetChange();
		cb_fullscreen->resetChange();
		cb_vsynch->resetChange();
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
	sl_framerate->render(window);
	ddl_resolutions->render(window);
	cb_fullscreen->render(window);
	cb_vsynch->render(window);
}

void SettingsState::endState()
{
	ddl_resolutions->resetChange();
	sl_musicVol->resetChange();
	sl_soundsVol->resetChange();
	sl_framerate->resetChange();
	cb_fullscreen->resetChange();
	cb_vsynch->resetChange();

	quit = true;
}

void SettingsState::initKeybinds()
{
}

void SettingsState::initButtons()
{
	float w = background.getSize().x * 0.09f;
	float x = background.getPosition().x + background.getSize().x / 2.f - 20.f - w;
	float y = background.getPosition().y + background.getSize().y / 2.f - 20.f - w / 1.7f;
	buttons["Exit"] = new Button("Exit", x, y, &fonts.get(Fonts::Arial), w, w / 1.7f);
	buttons["Apply"] = new Button("Apply", buttons["Exit"]->getPosition().x - w - 10.f, y,
		&fonts.get(Fonts::Arial), w, w / 1.7f);
}

void SettingsState::initVariables()
{
	initElements();
	initButtons();
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
	sl_framerate->update(dt);
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

void SettingsState::initElements()
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

	sf::VideoMode dflt = sf::VideoMode::getFullscreenModes().front();
	float k = (float)window->getSize().x / dflt.width;
	unsigned int chSizeMenuText = static_cast<unsigned>(35.f * k);
	unsigned int chSizeElement = static_cast<unsigned>(20.f * k);

	if (chSizeMenuText < 10u) chSizeMenuText = 10u;
	if (chSizeElement < 10u) chSizeElement = 10u;

	musicText.setString("Music");
	soundsText.setString("Sounds");
	musicText.setFont(arial);
	soundsText.setFont(arial);
	musicText.setCharacterSize(chSizeMenuText);
	soundsText.setCharacterSize(chSizeMenuText);

	for (int i = 0; i < settingsTexts.size(); i++)
	{
		settingsTexts[i].setFont(arial);
		settingsTexts[i].setCharacterSize(chSizeMenuText);
		settingsTexts[i].setPosition(
			background.getPosition().x - background.getOrigin().x + 20.f,
			background.getPosition().y - background.getOrigin().y
			+ 20.f + (settingsTexts[i].getGlobalBounds().height + i * background.getSize().y * 0.15f));
	}

	float w1 = settingsTexts[0].getPosition().x + settingsTexts[0].getGlobalBounds().width + 20.f;

	float w = background.getSize().x;
	float y = background.getSize().y;

	ddl_resolutions = new DropDownList<sf::VideoMode>(w * 0.25f, w * 0.25f / 12.f,
		w1, settingsTexts[0].getPosition().y, &fonts.get(Fonts::Arial));

	std::vector<sf::VideoMode> availableModes = sf::VideoMode::getFullscreenModes();
	for (size_t i = 0; i < availableModes.size(); i++)
	{
		ddl_resolutions->add(availableModes[i], std::to_string(availableModes[i].width)
			+ "x" + std::to_string(availableModes[i].height));
	}

	ddl_resolutions->setActiveValue(settings->resolution,
		std::to_string(settings->resolution.width) + "x" + std::to_string(settings->resolution.height));

	sl_framerate = new Slider(w * 0.25f, w * 0.25f / 12.f,
		w1, settingsTexts[1].getPosition().y, 20, 240, &mousePosWindow);
	sl_framerate->setFont(&fonts.get(Fonts::Arial));

	cb_fullscreen = new Checkbox(settingsTexts[3].getGlobalBounds().height,
		w1, settingsTexts[2].getPosition().y, settings->fullscreen);

	cb_vsynch = new Checkbox(settingsTexts[3].getGlobalBounds().height,
		w1, settingsTexts[3].getPosition().y, settings->vsynch);

	sl_musicVol = new Slider(w * 0.25f, w * 0.25f / 12.f,
		background.getPosition().x + background.getGlobalBounds().width / 2.f
		- 20.f - w * 0.25f, ddl_resolutions->getPosition().y, 0, 100, &mousePosWindow, "%");
	sl_musicVol->setFont(&fonts.get(Fonts::Arial));

	sl_soundsVol = new Slider(w * 0.25f, w * 0.25f / 12.f,
		sl_musicVol->getPosition().x, sl_framerate->getPosition().y, 0, 100, &mousePosWindow, "%");
	sl_soundsVol->setFont(&fonts.get(Fonts::Arial));

	musicText.setPosition(
		sl_musicVol->getPosition().x - 20.f - musicText.getGlobalBounds().width,
		settingsTexts[0].getPosition().y);

	soundsText.setPosition(
		sl_soundsVol->getPosition().x - 20.f - soundsText.getGlobalBounds().width,
		settingsTexts[1].getPosition().y);

	ddl_resolutions->setCharSize(chSizeElement);
	sl_framerate->setCharSize(chSizeElement);
	sl_musicVol->setCharSize(chSizeElement);
	sl_soundsVol->setCharSize(chSizeElement);

	sl_framerate->setValue(settings->framerate);
	sl_musicVol->setValue(settings->musicVolume);
	sl_soundsVol->setValue(settings->soundsVolume);
}