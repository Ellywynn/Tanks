#include "SettingsContainer.h"

SettingsContainer::SettingsContainer()
{
	resolution = sf::VideoMode::getDesktopMode();
	title = "Tanks";
	framerate = 120;
	fullscreen = false;
	vsynch = false;
	musicVolume = 50;
	soundsVolume = 50;
}

SettingsContainer::~SettingsContainer()
{
}

void SettingsContainer::loadFromFile(const std::string& filename)
{
	std::ifstream wcfg(filename);

	if (wcfg.is_open()) {
		resolution.width = std::stoi(getValue(wcfg));
		resolution.height = std::stoi(getValue(wcfg));
		title = getValue(wcfg);
		framerate = std::stoi(getValue(wcfg));
		fullscreen = std::stoi(getValue(wcfg));
		vsynch = std::stoi(getValue(wcfg));
		musicVolume = std::stoi(getValue(wcfg));
		soundsVolume = std::stoi(getValue(wcfg));
	}
	else {
		std::cerr << "[ERROR]: Cannot open file " + filename << '\n';
	}

	wcfg.close();
}

void SettingsContainer::saveToFile(const std::string& filename)
{
	std::ofstream wcfg(filename);

	if (wcfg.is_open()) {
		wcfg << "width: " << resolution.width << '\n';
		wcfg << "height: " << resolution.height << '\n';
		wcfg << "window title: " << title << '\n';
		wcfg << "framerate: " << framerate << '\n';
		wcfg << "fullscreen: " << static_cast<int>(fullscreen) << '\n';
		wcfg << "vertical synch: " << static_cast<int>(vsynch) << '\n';
		wcfg << "music volume: " << musicVolume << '\n';
		wcfg << "sounds volume: " << soundsVolume << '\n';
	}
	else {
		std::cerr << "[ERROR]: Cannot open file " + filename << '\n';
	}

	wcfg.close();
}

void SettingsContainer::setDefaultSettings(const std::string& filename)
{
	resolution = sf::VideoMode::getDesktopMode();
	title = "Tanks";
	framerate = 120;
	fullscreen = false;
	vsynch = false;
	musicVolume = 50;
	soundsVolume = 50;
	
	saveToFile();
}

std::string SettingsContainer::getValue(std::ifstream& file)
{
	std::string fileline = "";
	std::getline(file, fileline);
	return fileline.substr(fileline.find(":") + 2);
}
