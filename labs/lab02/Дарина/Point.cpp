#include <iostream>
#include <string>
using namespace std;

class Point {
protected:
	double x, y;

public:
	Point() { x = 0; y = 0; }
	Point(double xVal, double yVal) {
		x = xVal;
		y = yVal;
	}

	void setX(double xVal) { x = xVal; }
	void sety(double yVal) { y = yVal; }

	double getX() { return x; }
	double getY() { return y; }

	void print() {
		cout << "Point: (" << x << ", " << y << ")" << endl;
	}
};

class Point3D : public Point {
protected:
	double z;

public:
	Point3D() : Point() { z = 0; }

	Point3D(double xVal, double yVal, double zVal)
		: Point(xVal, yVal) {
		z = zVal;
	}

	void setZ(double zVal) { z = zVal; }
	double getZ() { return z; }

	void print() {
		cout << "Point3D: (" << x << ", " << y << ", " << z << ")" << endl;
	}
};

class PointColor : public Point {
protected:
	string color;

public:
	PointColor() : Point() { color = "green"; }

	PointColor(double xVal, double yVal, string col)
		: Point(xVal, yVal) {
		color = col;
	}

	void setColor(string col) { color = col; }
	string getColor() { return color; }

	void print() {
		cout << "PointColor: (" << x << ", " << y << "), color: " << color << endl;
	}
};

class Point3DColor : public Point3D {
private:
	string color;

public:
	Point3DColor() : Point3D() { color = "green"; }

	Point3DColor(double xVal, double yVal, double zVal, string col)
		: Point3D(xVal, yVal, zVal) {
		color = col;
	}

	void setColor(string col) { color = col; }
	string getColor() { return color; }

	void print() {
		cout << "Point3DColor: (" << x << ", " << y << ", " << z << "), color: " << color << endl;
	}
};

int main() {
	Point p(3, 5);
	Point3D p3(2, 4, 6);
	PointColor pc(8, 10, "pink");
	Point3DColor p3c(1, 7, 9, "blue");

	p.print();
	p3.print();
	pc.print();
	p3c.print();

	return 0;
}
