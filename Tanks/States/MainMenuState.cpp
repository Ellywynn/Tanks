#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window,
	std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	std::cout << "Main menu State\n";
	initKeybinds();
	loadAssets();
	initSprites();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto& b : buttons)
		delete b.second;
}

void MainMenuState::initKeybinds()
{
	std::ifstream file("config/gamestate_keybinds.ini");

	if (file.is_open()) {
		std::string key = "";
		std::string value = "";
		while (file >> key >> value) {
			keybinds[key] = supportedKeys->at(value);
		}
	}
	else {
		std::cerr << "[ERROR]: Cannot open file gamestate_keybinds.ini\n";
	}

	file.close();
}

void MainMenuState::initButtons()
{
	buttons["Play"] = new Button("Play", 30.f, 100.f, &fonts.get(Fonts::Arial));
	buttons["Exit"] = new Button("Exit", 30.f, 300.f, &fonts.get(Fonts::Arial));
}

void MainMenuState::initVariables()
{
}

void MainMenuState::updateButtons()
{
	updateMousePositions();
	for (auto& b : buttons)
		b.second->update(event, mousePosWindow);
	if (buttons["Play"]->isButtonPressed())
		pushGameState();
	if (buttons["Exit"]->isButtonPressed())
		quitState();
}

void MainMenuState::loadAssets()
{
	loadTextures();
	loadSounds();
	loadFonts();
	initSprites();
}

void MainMenuState::loadTextures()
{
	textures.load(Textures::MainMenu_Background, "assets/textures/MainMenu/background.jpg");
}


void MainMenuState::loadSounds()
{
}

void MainMenuState::loadFonts()
{
	fonts.load(Fonts::Arial, "assets/fonts/arial.ttf");
}

void MainMenuState::initSprites()
{
	sprites["background"] = createSprite(textures.get(Textures::MainMenu_Background));
}

void MainMenuState::pushGameState()
{
	buttons["Play"]->reset();
	states->push(new GameState(window, supportedKeys, states));
}

sf::Sprite MainMenuState::createSprite(sf::Texture& texture)
{
	sf::Sprite sprite(texture);
	return sprite;
}

void MainMenuState::updateInput(const float dt)
{
	
}

void MainMenuState::quitState()
{
	buttons["Exit"]->reset();
	quit = true;
}

void MainMenuState::endState()
{
	std::cout << "Ending main menu state\n";
}

void MainMenuState::handleEvents()
{
	while (window->pollEvent(event)) {
		updateButtons();
	}
}

void MainMenuState::update(const float dt)
{
	updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	for (auto& s : sprites)
		window->draw(s.second);
	for (auto& b : buttons)
		b.second->render(*window);
}