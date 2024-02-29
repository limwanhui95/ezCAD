#pragma once
class Point {
public:
	Point(float x, float y) : x(x), y(y) { z = 0; }
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point() { x = 0; y = 0; z = 0; }
	float x, y, z;
	Point operator + (Point const& obj) {
		Point ans;
		ans.x = x + obj.x;
		ans.y = y + obj.y;
		ans.z = z + obj.z;
		return ans;
	}
	Point operator - (Point const& obj) {
		Point ans;
		ans.x = x - obj.x;
		ans.y = y - obj.y;
		ans.z = z - obj.z;
	}
	Point operator * (float const& obj) {
		Point ans;
		ans.x = obj * x;
		ans.y = obj * y;
		ans.z = obj * z;
		return ans;
	}
};
