#pragma once
#include "Point.h"
#include <string>
#include <vector>

class graphicObject {
public:
	virtual void move(Point increment) = 0;
	virtual void rotate() = 0;
	virtual void copy() = 0;
	virtual void scale() = 0;
	virtual void mirror() = 0;
	unsigned int getID() { return ID; }
	virtual std::string printInfo() = 0;
	virtual std::string printType() = 0;
protected:
	void setID(unsigned int _ID) { ID = _ID; }
private:
	unsigned int ID;
};

class lineObject : public graphicObject {
public:
	virtual void move(Point increment) {}
	virtual void rotate() {}
	virtual void copy() {}
	virtual void scale() {}
	virtual void mirror() {}
	virtual std::string printInfo() { return ""; }
	virtual std::string printType() { return ""; }
	virtual void setVert(std::vector<float>* vert) {};
};

class areaObject : public graphicObject {
public:
	virtual void move(Point increment) {}
	virtual void rotate() {}
	virtual void copy() {}
	virtual void scale() {}
	virtual void mirror() {}
	virtual std::string printInfo() { return ""; }
	virtual std::string printType() { return ""; }
};