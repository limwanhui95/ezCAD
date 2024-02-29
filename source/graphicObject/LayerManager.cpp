#include "LayerManager.h"


LayerManager::LayerManager()
{
	LayerMap.try_emplace("default", new Layer("default"));
	std::unordered_map<std::string, Layer*>::iterator it = LayerMap.find("default");
	currentActiveLayer = it->second;
}

Layer* LayerManager::getCurrentActiveLayer()
{
	return currentActiveLayer;
}

void LayerManager::setCurrentActiveLayer(std::string Name)
{
	std::unordered_map<std::string, Layer*>::iterator it = LayerMap.find(Name);
	currentActiveLayer = it->second;
}

void LayerManager::deleteLayer(std::string Name)
{
	if (Name != "default") {
		std::unordered_map<std::string, Layer*>::iterator it = LayerMap.find(Name);
		std::unordered_map<std::string, Layer*>::iterator default_it = LayerMap.find("default");
		//if (default_it == LayerMap.end()) { std::cout << "Error"; }
		if (it != LayerMap.end()) {
			it->second->transferObj(default_it->second); // transfer all obj to default layer
			delete it->second;  // delete layer
			LayerMap.erase(it); // delete from hash map
		}
	}
}

int LayerManager::getNumberOfLayer()
{
	return LayerMap.size();
}

std::unordered_map<std::string, Layer*>::iterator LayerManager::getBegin()
{
	return LayerMap.begin();
}

std::unordered_map<std::string, Layer*>::iterator LayerManager::getEnd()
{
	return LayerMap.end();
}

Layer* LayerManager::getLayer(std::string Name)
{
	auto it = LayerMap.find(Name);
	if (it != LayerMap.end()) {
		return it->second;
	}
	return nullptr;
}

std::string LayerManager::getName(int index)
{
	auto it = LayerMap.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return it->second->getName();
}

void LayerManager::newLayer()
{
	std::string _name = getNewName();
	while (LayerMap.find(_name) != LayerMap.end()) { // same name exist
		defaultNameForNewLayer++;
		_name = getNewName();
	}
	LayerMap.try_emplace(_name, new Layer(_name));
	defaultNameForNewLayer++;
}

bool LayerManager::setName(int index, std::string name)
{
	// get pointer to layer
	Layer* selectedLayer = getLayer(getName(index));
	auto it = LayerMap.find(name);
	if (it != LayerMap.end()) {
		// repeated name found
		return false;
	}
	else {
		// update key value in map
		auto old = LayerMap.find(getName(index));
		LayerMap.erase(old); // remove from map & insert again at below
		LayerMap.emplace(name, selectedLayer);
		selectedLayer->setName(name);
		return true;
	}
	return true;
}


std::string LayerManager::getNewName()
{
	std::stringstream stream;
	stream << defaultNameForNewLayer;
	std::string nameForNewLayer;
	stream >> nameForNewLayer;
	return nameForNewLayer;
}
