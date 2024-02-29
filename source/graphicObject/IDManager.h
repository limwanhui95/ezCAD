#pragma once
#include <vector>
#include <unordered_map>
#include "graphicObject.h"

class IDManager {
public:
	IDManager() { pendingNewID = 1; }
	unsigned int registerNewID();
	void recycleID(unsigned int oldID);
	void bindID(unsigned int ID, graphicObject* obj);
	graphicObject* getObj(unsigned int ID);
private:
	std::vector<unsigned int> recycledID;
	unsigned int pendingNewID;
	std::unordered_map<unsigned int, graphicObject*> _map;
};
