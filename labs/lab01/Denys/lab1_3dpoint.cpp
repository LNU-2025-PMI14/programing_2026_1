

#include <iostream>
#include <string>
using namespace std;

class Point {
protected:
	int x;
	int y;
public:
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
	Point(const Point& a) : x(a.x), y(a.y) {};
	int getX() const { return x; }
	int getY() const { return y; }
	void print();
};

class Point3D : public Point {
protected:
	int z;
public:
	Point3D() : Point(), z(0) {};
	Point3D(int a, int b, int c) : Point(a, b), z(c) {};
	Point3D(const Point3D& a) : Point(a), z(a.z) {};
	int getZ() const { return z; }
	void print();
};

class ColorPoint : public Point {
protected:
	string color;
public:
	ColorPoint() : Point(), color("black") {};
	ColorPoint(int a, int b, string col = "black") : Point(a, b), color(col) {};
	ColorPoint(const ColorPoint& a) : Point(a), color(a.color) {};
	string getCol() const { return color; }
	void print();
};

class ColorPoint3D : public Point3D {
protected:
	string color;
public:
	ColorPoint3D() :Point3D(), color("black") {};
	ColorPoint3D(int a, int b, int c, string col) : Point3D(a, b, c), color(col) {};
	ColorPoint3D(const ColorPoint3D& a) : Point3D(a), color(a.color) {};
	string getCol() const { return color; }
	void print();
};

void Point::print() {
	cout << "your point: " << x << ' ' << y << '\n';
}

void Point3D::print()
{
	cout << "your 3D point: " << x << ' ' << y << ' ' << z << '\n';
}

void ColorPoint::print()
{
	cout << "your color point: " << x << ' ' << y << ' ' << color << '\n';
}

void ColorPoint3D::print()
{
	cout << "your 3D color point: " << x << ' ' << y << ' ' << z << ' ' << color << '\n';
}

int main()
{
	Point A(1, 4);
	Point3D B(2, 3, 5);
	A.print();
	B.print();
	ColorPoint3D C(1, 2, 3, "black");
	C.print();
}

