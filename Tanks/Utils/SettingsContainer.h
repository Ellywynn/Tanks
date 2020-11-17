#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class SettingsContainer
{
public:
	SettingsContainer();
	~SettingsContainer();

	void loadFromFile(const std::string& filename = "config/window.ini");
	void saveToFile(const std::string& filename = "config/window.ini");
	void setDefaultSettings(const std::string& filename = "config/window.ini");

	sf::VideoMode resolution;
	std::string title;
	int framerate;
	bool fullscreen;
	bool vsynch;
	int musicVolume;
	int soundsVolume;
private:
	std::string getValue(std::ifstream& file);
};

#endif