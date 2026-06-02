#include <iostream>
#include <string> //додали бібліотеку для роботи з текстом

using namespace std;

class Point {
protected:
	int x;
	int y;
public:
	Point() : x(0), y(0) {}
	Point(int xVal, int yVal) :x(xVal), y(yVal) {}
	int getX() const { return x; }
	void setX(int val) { x = val; }
	int getY() const { return y; }
	void setY(int val) { y = val; }

	virtual void print() const {
		cout << "Point(" << x << ", " << y << ")\n";
	}
};

class Point3D : virtual public Point {
protected:
	int z;
public:
	Point3D() : Point(), z(0) {}
	Point3D(int xVal, int yVal, int zVal) : Point(xVal, yVal), z(zVal) {}
	int getZ() const { return z; }
	void setZ(int val) { z = val; }
	void print() const override {
		cout << "Point3D(" << x << ", " << y << ", " << z << ")\n";
	}
};

class PointColor : virtual public Point {
protected:
	string color;
public:
	PointColor() : Point(), color("black") {}
	PointColor(int xVal, int yVal, string cVal) : Point(xVal, yVal), color(cVal) {}
	string getColor() const { return color; }
	void setColor(string val) { color = val; }
	void print() const override {
		cout << "PointColor(" << x << ", " << y << ", Color: " << color << ")\n";
	}
};

class Point3DColor : public Point3D, public PointColor {
public:
	Point3DColor() : Point(), Point3D(), PointColor() {}
	Point3DColor(int xVal, int yVal, int zVal, string cVal)
		: Point(xVal, yVal), Point3D(xVal, yVal, zVal), PointColor(xVal, yVal, cVal) {
	}

	void print() const override {
		cout << "Point3DColor(" << x << ", " << y << ", " << z << ", Color: " << color << ")" << endl;
	}
};

int main()
{
	Point p1(10, 20);
	p1.print();

	Point3D p3d(10, 20, 30);
	p3d.print();

	PointColor pc(5, 5, "red");
	pc.print();

	Point3DColor p3dc(1, 2, 3, "blue");
	p3dc.print();

	return 0;
}