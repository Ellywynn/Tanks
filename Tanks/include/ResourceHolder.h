#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <cstdint>
#include <fstream>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

template<typename Resource, typename Name>
class ResourceHolder {
public:
	ResourceHolder() {}
	~ResourceHolder() {}

	inline void load(Name name, const std::string& filename) {
		std::unique_ptr<Resource> res(new Resource());

		if (!res->loadFromFile(filename)) {
			std::cerr << "[RH ERROR]: Can't load file \"" + filename + "\"\n";
			return;
		}

		resources.insert(std::make_pair(name,std::move(res)));
	}

	inline Resource& get(Name name) {
		auto found = resources.find(name);
		assert(found != resources.end() && "[RH ERROR]: Can't get the file\n");
		return *found->second;
	}

	inline const Resource& get(Name name) const {
		auto found = resources.find(name);
		assert(found != resources.end() && "[RH ERROR]: Can't get the file\n");
		return *found->second;
	}

private:
	std::unordered_map<Name, std::unique_ptr<Resource>> resources;
};

#endif