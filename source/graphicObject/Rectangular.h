#pragma once
#include "Point.h"
#include "graphicObject.h"
#include <sstream>

class Rectangular : public lineObject {
public:
	Rectangular(Point a, Point b, Point c, Point d, int ID) {
		_point[0] = a;
		_point[1] = b;
		_point[2] = c;
		_point[3] = d;
		setID(ID);
	}
	Point getPoint1() {
		return _point[0];
	}
	Point getPoint2() {
		return _point[1];
	}
	Point getPoint3() {
		return _point[2];
	}
	Point getPoint4() {
		return _point[3];
	}
	virtual void move(Point increment) {
		for (int i = 0; i < 4; i++) {
			_point[i] = _point[i] + increment;
		}
	}
	virtual std::string printInfo() {
		std::string temp = "(";
		std::string temp2;
		std::stringstream stream;
		for (int i = 0; i < 4; i++) {
			stream << _point[i].x;
			stream >> temp2;
			stream.clear();
			temp = temp + temp2 + ",";
			stream << _point[i].y;
			stream >> temp2;
			stream.clear();
			if (i != 3) {
				temp = temp + temp2 + ") (";
			}
			else{
				temp = temp + temp2 + ")";
			}
		}
		return temp;
	}
	virtual std::string printType() {
		return "Rectangular";
	}
	virtual void setVert(std::vector<float>* vert) {
		for (int i = 0; i < 3; i++) {
			vert->emplace_back(_point[i].x);
			vert->emplace_back(_point[i].y);
			vert->emplace_back(_point[i].z);

			vert->emplace_back(_point[i+1].x);
			vert->emplace_back(_point[i+1].y);
			vert->emplace_back(_point[i+1].z);
		}
		vert->emplace_back(_point[3].x);
		vert->emplace_back(_point[3].y);
		vert->emplace_back(_point[3].z);
		vert->emplace_back(_point[0].x);
		vert->emplace_back(_point[0].y);
		vert->emplace_back(_point[0].z);
	}
private:
	Point _point[4];
};