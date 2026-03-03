#include <iostream>
#include <string>

using namespace std;

class Point {
private:
	int x, y;
public:
	Point() : x(0), y(0) {}
	Point(int xval, int yval) : x(xval), y(yval) {}
	Point(const Point& p) {
		x = p.get_x();
		y = p.get_y();
	}

	int get_x() const {
		return x;
	}

	int get_y() const {
		return y;
	}

	void set_x(int xval) {
		x = xval;
	}

	void set_y(int yval) {
		y = yval;
	}

	virtual void print() {
		cout << '(' << x << ", " << y << ')' << '\n';
	}
};

class Point3D : virtual public Point {
private:
	int z;
public:
	Point3D() : Point(), z(0) {}
	Point3D(int xval, int yval, int zval) : Point(xval, yval), z(zval) {}
	Point3D(const Point3D& p) : Point(p), z(p.get_z()){}

	int get_z() const {
		return z;
	}

	void set_z(int zval) {
		z = zval;
	}

	void print() override {
		cout << '(' << this->get_x() << ", " << this->get_y() << ", " << this->get_z() << ')' << '\n';
	}
};

class PointColor : virtual public Point {
private:
	string color;
public:
	PointColor() : Point(), color("black") {}
	PointColor(int xval, int yval, string colorval = "black") : Point(xval, yval), color(colorval) {}
	PointColor(const PointColor& p) : Point(p), color(p.get_color()){}

	string get_color() const {
		return color;
	}

	void set_color(string val) {
		color = val;
	}

	void print() override {
		cout << '(' << this->get_x() << ", " << this->get_y() << ')' << " : " << this->get_color() << '\n';
	}
};

class Point3DColor : public Point3D, public PointColor {
public:
	Point3DColor() : Point(), Point3D(), PointColor() {}
	Point3DColor(int xval, int yval, int zval, string colorval = "black") : Point(xval, yval), Point3D(xval, yval, zval), PointColor(xval, yval, colorval) {}

	Point3DColor(const Point3DColor& p) : Point(p), Point3D(p), PointColor(p) {}

	void print() override {
		cout << '(' << this->get_x() << ", " << this->get_y() << ", " << this->get_z() << ')' << " : " << this->get_color() << '\n';
	}
};

int main()
{
	Point p;
	Point3D p3d(1, 3, 4);
	PointColor pcolor(0, 0, "red");
	Point3DColor p3dcolr(1, 2, 4, "pink");
    
	p.print();
	p3d.print();
	pcolor.print();
	p3dcolr.print();
}
