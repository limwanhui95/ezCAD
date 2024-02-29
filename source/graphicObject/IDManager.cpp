#include "IDManager.h"

unsigned int IDManager::registerNewID()
{
    int newID;
    if (recycledID.empty()) {
        newID = pendingNewID;
        pendingNewID++;
    }
    else {
        newID = *(recycledID.end() - 1);
        recycledID.pop_back();
    }
    return newID;
}

void IDManager::recycleID(unsigned int oldID)
{
    recycledID.push_back(oldID);
}

void IDManager::bindID(unsigned int ID, graphicObject* obj)
{
    _map.try_emplace(ID, obj);
}


graphicObject* IDManager::getObj(unsigned int ID)
{
    std::unordered_map<unsigned int, graphicObject*>::iterator it;
    it = _map.find(ID);
    if (it != _map.end()) {
        graphicObject* pt = _map.find(ID)->second;
        return pt;
    }
    return nullptr;
}

