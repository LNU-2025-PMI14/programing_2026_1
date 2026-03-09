#include <string>
#include <iostream>

class Point {
protected:
	int x;
	int y;
public:
	Point() : x(0), y(0) {};
	Point(int x, int y) : x(x), y(y) {};
	Point(const Point& a) : x(a.x), y(a.y) {};

	int getX() const { return x; };
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setPoint(int x, int y) {
		this->x = x;
		this->y = y;
	}

	virtual void print() const {
		std::cout << "Point: " << x << ' ' << y << '\n';
	};
	virtual ~Point() {};
};



class Point3D : public Point {
protected:
	int z;
public:
	Point3D() : Point(), z(0) {};
	Point3D(int x, int y, int z) : Point(x, y), z(z) {};
	Point3D(const Point3D& a) : Point(a), z(a.z) {};

	void print() const override {
		std::cout << "Point3D: " << x << ' ' << y << ' ' << z << '\n';
	};

	int getZ() const { return z; }
	void setZ(int z) { this->z = z; }
	void setPoint3D(int x, int y, int z) {
		setX(x);
		setY(y);
		this->z = z;
	}
	~Point3D() {};
};


class PointColor : public Point {
protected:
	std::string color;
public:
	PointColor() : Point(), color("Red") {};
	PointColor(int x, int y, const std::string& color) : Point(x, y), color(color) {};
	PointColor(const PointColor& a) : Point(a), color(a.color) {};

	void print() const override { std::cout << "PointColor: " << x << ' ' << y << ' ' << color << '\n'; };

	std::string getColor() const { return color; }
	void setColor(const std::string& color) { this->color = color; }
	void setPointColor(int x, int y, const std::string& color) {
		setX(x);
		setY(y);
		this->color = color;
	}
	~PointColor() {};
};



class Point3DColor : public Point3D {
protected:
	std::string color;
public:
	Point3DColor() : Point3D(), color("Black") {};
	Point3DColor(int x, int y, int z, const std::string& c) : Point3D(x, y, z), color(c) {};
	Point3DColor(const Point3DColor& a) : Point3D(a), color(a.color) {};

	void print() const override {
		std::cout << "Point3DColor: " << x << ' ' << y << ' ' << z << ' ' << color << '\n';
	};

	std::string getColor() const { return color; }
	void setColor(const std::string& color) { this->color = color; }
	void setPoint3DColor(int x, int y, int z, const std::string& color) {
		setX(x);
		setY(y);
		setZ(z);
		this->color = color;
	}
	~Point3DColor() {};
};
int main()
{
	Point A(10, 20);
	A.print();

	Point3D B(20, 30, 40);
	B.print();

	PointColor D;
	D.print();

	Point3DColor Z;
	Z.print();
}
