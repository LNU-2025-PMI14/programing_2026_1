#include <iostream>
using namespace std;

class Point {
protected:
    double x;
    double y;

public:
    
    Point() : x(0), y(0) {}
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    void setX(double xVal) { x = xVal; }
    void setY(double yVal) { y = yVal; }
    void setPoint(double xVal, double yVal) {
        x = xVal;
        y = yVal;
    }
    double getX() const { return x; }
    double getY() const { return y; }

 
    void print() const {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};
class Point3D : public Point {
protected:
    double z;

public:
    Point3D() : Point(), z(0) {}
    Point3D(double xVal, double yVal, double zVal)
        : Point(xVal, yVal), z(zVal) {
    }


    void setZ(double zVal) { z = zVal; }

    double getZ() const { return z; }

    void setPoint3D(double xVal, double yVal, double zVal) {
        x = xVal;
        y = yVal;
        z = zVal;
    }

    void print() const {
        cout << "Point3D(" << x << ", " << y << ", " << z << ")" << endl;
    }
};
class ColorPoint : public Point {
protected:
    string color;

public:
    ColorPoint() : Point(), color("white") {}
    ColorPoint(double xVal, double yVal, string col)
        : Point(xVal, yVal), color(col) {
    }

    void setColor(string col) { color = col; }
    string getColor() const { return color; }

    void print() const {
        cout << "ColorPoint(" << x << ", " << y
            << ", color: " << color << ")" << endl;
    }
};

class ColorPoint3D : public Point3D {
private:
    string color;

public:
    ColorPoint3D() : Point3D(), color("white") {}
    ColorPoint3D(double xVal, double yVal, double zVal, string col)
        : Point3D(xVal, yVal, zVal), color(col) {
    }


    void setColor(string col) { color = col; }
    string getColor() const { return color; }

    void print() const {
        cout << "ColorPoint3D(" << x << ", " << y
            << ", " << z
            << ", color: " << color << ")" << endl;
    }
};
int main() {
    Point p(2, 3);
    Point3D p3(1, 2, 3);
    ColorPoint cp(5, 6, "red");
    ColorPoint3D cp3(7, 8, 9, "blue");

    p.print();
    p3.print();
    cp.print();
    cp3.print();

    return 0;
}