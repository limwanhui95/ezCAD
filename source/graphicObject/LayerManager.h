#pragma once
#include <unordered_map>
#include "Layer.h"

#include <sstream>
#include <iostream>

class LayerManager {
public:
	LayerManager();
	Layer* getCurrentActiveLayer();
	void setCurrentActiveLayer(std::string Name);
	void deleteLayer(std::string Name);
	int getNumberOfLayer();
	std::unordered_map<std::string, Layer*>::iterator getBegin();
	std::unordered_map<std::string, Layer*>::iterator getEnd();
	Layer* getLayer(std::string Name);
	std::string getName(int index);
	void newLayer();
	bool setName(int index, std::string name);
private:
	int defaultNameForNewLayer = 1;
	std::unordered_map<std::string, Layer*> LayerMap;
	Layer* currentActiveLayer;
	std::string getNewName();
};