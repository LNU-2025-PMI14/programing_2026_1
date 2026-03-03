#include <iostream>
#include <string>

using namespace std;

/*створити клас Point, Point 3D, Point Color,
Point 3DColor.Визначит всі getter та setter, 
конструктори та методи для роботи з даними класами.*/

class Point{
	private:
		double x;
		double y;
	public:
		Point() : x(0), y(0) {}
		Point(double x, double y) : x(x), y(y) {}
		void setX(double x) {this->x = x;}
		void setY(double y) {this->y = y;}
		double getX() {return x;}
		double getY() {return y;}
		void print() {cout << "Point coordinates at ( x: " << x << ", y: " << y << ")" << endl;}
};

class Point3D: public Point{
	private:
		double z;
	public:
		Point3D() : Point(), z(0) {}
		Point3D(double x, double y, double z) : Point(x, y), z(z) {}
		void setZ(double z) {this->z = z;}
		double getZ() { return z;}
		void print() {cout << "Point3D coordinates at ( x: " << getX() << ", y: " << getY() << ", z: " << z << ")" << endl;}
};

class PointColor: public Point{
	private:
		string color;
	public:
		PointColor() : Point(), color("white") {}
		PointColor(double x, double y, string color) : Point(x, y), color(color) {}
		void setColor(string color) { this->color = color; }
		string getColor() { return color; }
		void print() {cout << "Point color " << color << " at ( x: " << getX() << ", y: " << getY() << " )" << endl;}
};

class Point3DColor : public Point3D {
	private:
		string color;
	public:
		Point3DColor() : Point3D(), color("white") {}
		Point3DColor(double x, double y, double z, string color): Point3D(x, y, z), color(color) {}
		void setColor(string color) { this->color = color; }
		string getColor() { return color; }
		void print() {cout << "Point color " << color << " at ( x: " << getX() << ", y: " << getY() << ", z: " << getZ() << " )" << endl;}
};
int main() {
	Point p(-5, 0);
	Point3D p3(53, 67, 6);
	PointColor pc(200, -9, "red");
	Point3DColor p3c(89, 49, 0, "blue");

	p.print();
	p3.print();
	pc.print();
	p3c.print();

	return 0;
}