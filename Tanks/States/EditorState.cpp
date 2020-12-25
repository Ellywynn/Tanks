#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::unordered_map<std::string, int>* supportedKeys,
	std::stack<State*>* states, SettingsContainer& settings) : State(window, supportedKeys, states)
{
	this->settings = &settings;
	initKeybinds();
	loadAssets();
	initSprites();
	initButtons();
}

EditorState::~EditorState()
{
}

void EditorState::endState()
{
}

void EditorState::handleEvents()
{
}

void EditorState::update(const float dt)
{
}

void EditorState::render(sf::RenderTarget* target)
{
}

void EditorState::updateButtons()
{
}

void EditorState::updateInput(const float dt)
{
}

void EditorState::initKeybinds()
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

void EditorState::initButtons()
{ 
	sf::Font& font = fonts.get(Fonts::Arial);
	
	buttons["Exit"] = new Button("Exit", 30.f, 350.f, &font);
}

void EditorState::initVariables()
{
}

void EditorState::initSprites()
{
}

void EditorState::loadAssets()
{
}

void EditorState::loadTextures()
{
}

void EditorState::loadSounds()
{
}

void EditorState::loadFonts()
{
}

void EditorState::quitState()
{
}

void EditorState::pushSettingsState()
{
}