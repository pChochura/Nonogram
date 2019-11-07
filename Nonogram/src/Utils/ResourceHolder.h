#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier id, std::string filename) {
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}

		insertResource(id, std::move(resource));
	}

	Resource& get(Identifier id) const {
		return *mResourceMap.find(id)->second;
	}

protected:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource) {
		mResourceMap.insert(std::make_pair(id, std::move(resource)));
	}

protected:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};