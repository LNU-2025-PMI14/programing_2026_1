#include <iostream>
#include <string>
using namespace std;

class Point {
protected:
    int posX, posY;

public:
    Point(int posX = 1, int posY = 1) {
        this->posX = posX;
        this->posY = posY;
    }

    int readX() { return posX; }
    int readY() { return posY; }

    void writeX(int posX) { this->posX = posX; }
    void writeY(int posY) { this->posY = posY; }

    void print() {
        cout << "Object Point: x = " << posX << ", y = " << posY << endl;
    }
};


class Point3D : public Point {
protected:
    int posZ;

public:
    Point3D(int posX = 1, int posY = 1, int posZ = 1) : Point(posX, posY) {
        this->posZ = posZ;
    }

    int readZ() { return posZ; }
    void writeZ(int posZ) { this->posZ = posZ; }

    void print() {
        cout << "Object Point3D: x = " << posX << ", y = " << posY << ", z = " << posZ << endl;
    }
};


class PointColor : public Point {
protected:
    string pointColor;

public:
    PointColor(int posX = 1, int posY = 1, string pointColor = "none")
        : Point(posX, posY) {
        this->pointColor = pointColor;
    }

    string readColor() { return pointColor; }
    void writeColor(string pointColor) { this->pointColor = pointColor; }

    void print() {
        cout << "Object PointColor: x = " << posX << ", y = " << posY
            << ", color = " << pointColor << endl;
    }
};


class Point3DColor : public Point3D {
protected:
    string pointColor;

public:
    Point3DColor(int posX = 1, int posY = 1, int posZ = 1, string pointColor = "none")
        : Point3D(posX, posY, posZ) {
        this->pointColor = pointColor;
    }

    string readColor() { return pointColor; }
    void writeColor(string pointColor) { this->pointColor = pointColor; }

    void print() {
        cout << "Object Point3DColor: x = " << posX
            << ", y = " << posY
            << ", z = " << posZ
            << ", color = " << pointColor << endl;
    }
};

int main() {
    Point p(10, 20);
    p.print();

    Point3D p3(30, 40, 50);
    p3.print();

    PointColor pc(60, 70, "green");
    pc.print();

    Point3DColor p3c(80, 90, 100, "yellow");
    p3c.print();

    return 0;
}