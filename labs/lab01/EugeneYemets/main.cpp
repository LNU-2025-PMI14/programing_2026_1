#include <iostream>
#include <string>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}

    virtual ~Point() {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    void setPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }

    virtual void print() const {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }
};

class Point3D : public Point {
private:
    int z;

public:
    Point3D() : Point(), z(0) {}
    Point3D(int x, int y, int z) : Point(x, y), z(z) {}
    Point3D(const Point3D& other) : Point(other), z(other.z) {}

    int getZ() const {
        return z;
    }

    void setZ(int z) {
        this->z = z;
    }

    void setPoint3D(int x, int y, int z) {
        setX(x);
        setY(y);
        this->z = z;
    }

    void print() const override {
        cout << "Point3D: (" << getX() << ", " << getY() << ", " << z << ")" << endl;
    }
};

class PointColor : public Point {
private:
    string color;

public:

    PointColor() : Point(), color("black") {}
    PointColor(int x, int y, const string& color) : Point(x, y), color(color) {}
    PointColor(const PointColor& other) : Point(other), color(other.color) {}

    string getColor() const {
        return color;
    }

    void setColor(const string& color) {
        this->color = color;
    }

    void setPointColor(int x, int y, const string& color) {
        setX(x);
        setY(y);
        this->color = color;
    }

    void print() const override {
        cout << "PointColor: (" << getX() << ", " << getY() << "), color = " << color << endl;
    }
};

class Point3DColor : public Point3D {
private:
    string color;

public:
    Point3DColor() : Point3D(), color("black") {}
    Point3DColor(int x, int y, int z, const string& color)
        : Point3D(x, y, z), color(color) {}
    Point3DColor(const Point3DColor& other)
        : Point3D(other), color(other.color) {}

    string getColor() const {
        return color;
    }

    void setColor(const string& color) {
        this->color = color;
    }

    void setPoint3DColor(int x, int y, int z, const string& color) {
        setX(x);
        setY(y);
        setZ(z);
        this->color = color;
    }

    void print() const override {
        cout << "Point3DColor: (" << getX() << ", " << getY() << ", " << getZ()
             << "), color = " << color << endl;
    }
};

int main() {
    Point p(1, 2);
    Point3D p3(3, 4, 5);
    PointColor pc(6, 7, "red");
    Point3DColor p3c(8, 9, 10, "blue");

    p.print();
    p3.print();
    pc.print();
    p3c.print();

    return 0;
}
