#pragma once
#include "graphicObject.h"
#include <vector>
#include <string>
#include "../imGui/imgui.h"

class Layer {
public:
	Layer(std::string Name) : Name(Name) {}
	bool isVisible();
	void setVisiblity(bool flag);
	bool* getVisibility();
	ImVec4* getColor();
	void setName(std::string _name);
	std::string getName();
	float* getWidth();
	void insertObj(lineObject* _obj);
	void transferObj(Layer* newLayer);
	std::vector<lineObject*>::iterator begin();
	std::vector<lineObject*>::iterator end();
	int getSizeOfObj();
private:
	bool _isVisible = true;
	ImVec4 color = ImVec4(0.0f,0.0f,0.0f,1.0f);
	float width = 1.0f;
	std::string Name;
	std::vector<lineObject*> obj;
};