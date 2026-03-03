#include <iostream>
#include <string>
using namespace std;
//ствоити клас  point, point 3d, point color, point 3d color, set get print  
class Point {
protected:
	int x;
	int y;

public:
	Point (int xVal, int yVal) : x(xVal), y(yVal){}

	int getX() const { return x; }
	int getY() const { return y; }

	void setX(int val) { x = val; }
	void setY(int val) { y = val; }

	virtual void print() const {
		cout << "Point: ( " << x << ", " << y << ") " << endl;
	}

};

class Point3D : public Point {
protected:
	int z;

public:
	Point3D (int xVal, int yVal, int zVal) : Point(xVal,yVal) , z(zVal){}

	int getZ() const { return z; }
	void setZ(int val) { z = val; }

	virtual void print() const override {
		cout << "Point 3D: ( " << x << ", " << y << ", " << z << ") " << endl;
	}
};

class PointColor : public Point {
protected:
	string color;
public:
	PointColor(int xVal, int yVal, string colorVal) : Point(xVal, yVal), color(colorVal) {}

	string getColor() const { return color; }
	void setColor(string val) { color = val; }

	virtual void print() const override {
		cout << "Point Color: ( " << x << ", " << y << " ) Color: " << color << endl;

	}
};

class Point3DColor : public Point3D {
protected:
	string color;
public:
	Point3DColor(int xVal, int yVal, int zVal, string colorVal) : Point3D(xVal, yVal,zVal), color(colorVal) {}

	string getColor() const { return color; }
	void setColor(string val) { color = val; }

	virtual void print() const override {
		cout << "Point 3D Color: ( " << x << ", " << y << ", " << z << " ) Color: " << color << endl;
	}
};