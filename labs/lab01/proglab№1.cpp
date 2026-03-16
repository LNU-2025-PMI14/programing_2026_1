#include <iostream>
#include <string>

using namespace std;

class Point {
protected:
    double x;
    double y;

public:
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double val) { x = val; }
    void setY(double val) { y = val; }

    virtual void print() const {
        cout << "[Point] Coordinates: X=" << x << ", Y=" << y << endl;
    }
};

class Point3D : public Point {
protected:
    double z;

public:
    Point3D(double xVal, double yVal, double zVal) : Point(xVal, yVal), z(zVal) {}

    double getZ() const { return z; }
    void setZ(double val) { z = val; }

    virtual void print() const override {
        cout << "[Point3D] Coordinates: X=" << x << ", Y=" << y << ", Z=" << z << endl;
    }
};

class PointColor : public Point {
protected:
    string color;

public:
    PointColor(double xVal, double yVal, string colorVal) : Point(xVal, yVal), color(colorVal) {}

    string getColor() const { return color; }
    void setColor(string val) { color = val; }

    virtual void print() const override {
        cout << "[PointColor] Coordinates: X=" << x << ", Y=" << y << " | Color: " << color << endl;
    }
};

class Point3DColor : public Point3D {
protected:
    string color;

public:
    Point3DColor(double xVal, double yVal, double zVal, string colorVal) : Point3D(xVal, yVal, zVal), color(colorVal) {}

    string getColor() const { return color; }
    void setColor(string val) { color = val; }

    virtual void print() const override {
        cout << "[Point3DColor] Coordinates: X=" << x << ", Y=" << y << ", Z=" << z << " | Color: " << color << endl;
    }
};

int main() {
    Point p1(5.5, 12.0);
    p1.print();

    Point3D p2(1.0, 2.0, 3.0);
    p2.setZ(99.9);
    p2.print();

    PointColor p3(15.0, 25.0, "Crimson Red");
    p3.print();

    Point3DColor p4(7.5, 8.5, 9.5, "Ocean Blue");
    p4.setColor("Emerald Green");
    p4.print();

    return 0;
}