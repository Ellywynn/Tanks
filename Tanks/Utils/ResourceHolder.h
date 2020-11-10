#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

// std stuff
#include <cstdint>
#include <fstream>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cassert>

// SFML stuff
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/*
	This generic class allows to easy load and get any media files.
	It has get and load functions. It works like std::map container.
	Also, this class uses enums to decide which texture/sound/font to load or return.
*/
template<typename Resource, typename Name>
class ResourceHolder {
public:
	ResourceHolder() {}
	~ResourceHolder() {}

	// Loads new resource to the container
	inline void load(Name name, const std::string& filename) {
		// Create new resource
		std::unique_ptr<Resource> res(new Resource());

		// Loads this resource from file
		if (!res->loadFromFile(filename)) {
			// If it didn't load, get an error
			std::cerr << "[RH ERROR]: Can't load file \"" + filename + "\"\n";
			return;
		}

		// Insert new resource into the container
		resources.insert(std::make_pair(name,std::move(res)));
	}

	// Get resource by the resource type
	inline Resource& get(Name name) {
		// Find the resource
		auto found = resources.find(name);
		// Throw an error if it can't find appropriate resource
		assert(found != resources.end() && "[RH ERROR]: Can't get the file\n");
		return *found->second;
	}

	// Get resource by the resource type
	inline const Resource& get(Name name) const {
		auto found = resources.find(name);
		assert(found != resources.end() && "[RH ERROR]: Can't get the file\n");
		return *found->second;
	}
private:
	// Resource container
	std::unordered_map<Name, std::unique_ptr<Resource>> resources;
};

#endif