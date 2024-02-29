#include "Layer.h"


bool Layer::isVisible()
{
	return _isVisible;
}

void Layer::setVisiblity(bool flag)
{
	_isVisible = flag;
}

bool* Layer::getVisibility()
{
	return &_isVisible;
}

ImVec4* Layer::getColor()
{
	return &color;
}



void Layer::setName(std::string _name)
{
	Name = _name;
}

std::string Layer::getName()
{
	return Name;
}

float* Layer::getWidth()
{
	return &width;
}

void Layer::insertObj(lineObject* _obj)
{
	obj.emplace_back(_obj);
}

void Layer::transferObj(Layer* newLayer)
{
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		newLayer->insertObj(*it);
	}
}

std::vector<lineObject*>::iterator Layer::begin()
{
	return obj.begin();
}

std::vector<lineObject*>::iterator Layer::end()
{
	return obj.end();
}

int Layer::getSizeOfObj()
{
	return obj.size();
}
