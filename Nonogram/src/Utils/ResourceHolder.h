#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
//	Class describing different resources such as:
//	fonts, textures, sounds.
////////////////////////////////////////////////////////////
template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	////////////////////////////////////////////////////////////
	//	Loads the file with the given {@param filename} and 
	//	saves it to the list with the given {@param id}.
	////////////////////////////////////////////////////////////
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