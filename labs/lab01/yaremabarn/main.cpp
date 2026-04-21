#include <iostream>
# include <cmath>
using namespace std;
class Point {
private:
	double x;
	double y;

public:
	Point(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}

	double getX() const { return x; }
	double getY() const { return y; }

	void setX(double xVal) { x = xVal; }
	void setY(double yVal) { y = yVal; }

	double distanceTo(const Point& other) const {
		return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
	}

	void display() const {
		cout << "Point(" << x << "," << y << ")" << endl;
	}

};

int main() {
	Point p1(7.8, 9.9);
	Point p2(10, 18.9);

	p1.display();
	p2.display();
	
	p1.setX(2228);
	p1.setY(2008);

	p2.setX(300);
	p2.setY(449);

	p1.display();
	p2.display();

	double dist = p1.distanceTo(p2);
	cout << "_________DISTANCE___________" << endl;
	cout << dist << endl;


	return 0;
