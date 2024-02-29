#pragma once
#include "Point.h"
#include "graphicObject.h"
#include <sstream>
#include <iostream>

class Line : public lineObject {
public:
	Line(Point a, Point b, int ID) {
		_point[0] = a;
		_point[1] = b;
		setID(ID);
		//std::cout << "ID created: " << getID() << std::endl;
	}
	Point getPoint1() {
		return _point[0];
	}
	Point getPoint2() {
		return _point[1];
	}
	virtual void move(Point increment) {
		_point[0] = _point[0] + increment;
		_point[1] = _point[1] + increment;
	}
	virtual std::string printInfo() {
		std::string temp = "Point A: x=";
		std::string temp2;
		std::stringstream stream;
		stream << _point[0].x;
		stream >> temp2;
		stream.clear();
		temp = temp + temp2 + " y=";
		stream << _point[0].y;
		stream >> temp2;
		stream.clear();
		temp = temp + temp2 + ". Point B: x=";
		stream << _point[1].x;
		stream >> temp2;
		stream.clear();
		temp = temp + temp2 + " y=";
		stream << _point[1].y;
		stream >> temp2;
		stream.clear();
		temp = temp + temp2;
		return temp;
	}
	virtual std::string printType() {
		return "Line";
	}
	virtual void setVert(std::vector<float>* vert) {
		vert->emplace_back(_point[0].x);
		vert->emplace_back(_point[0].y);
		vert->emplace_back(_point[0].z);
		vert->emplace_back(_point[1].x);
		vert->emplace_back(_point[1].y);
		vert->emplace_back(_point[1].z);
	}
private:
	Point _point[2];
};
