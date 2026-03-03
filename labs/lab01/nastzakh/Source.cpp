#include <iostream>
#include <string>
using namespace std;

//створити клас поінт, поінт 3д, поінт колор, поінт 3д колор
//визначити всі геттери сеттери, конструктори і метод прінтт

class Point {
protected:
    int x, y;

public:
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    void print() {
        cout << "Point: x=" << x << ", y=" << y << endl;
    }
};


class Point3D : public Point {
protected:
    int z;

public:
    Point3D(int x = 0, int y = 0, int z = 0) : Point(x, y) {
        this->z = z;
    }

    int getZ() { return z; }
    void setZ(int z) { this->z = z; }

    void print() {
        cout << "Point3D: x=" << x << ", y=" << y << ", z=" << z << endl;
    }
};


class PointColor : public Point {
protected:
    string color;

public:
    PointColor(int x = 0, int y = 0, string color = "white")
        : Point(x, y) {
        this->color = color;
    }

    string getColor() { return color; }
    void setColor(string color) { this->color = color; }

    void print() {
        cout << "PointColor: x=" << x << ", y=" << y
            << ", color=" << color << endl;
    }
};


class Point3DColor : public Point3D {
protected:
    string color;

public:
    Point3DColor(int x = 0, int y = 0, int z = 0, string color = "white")
        : Point3D(x, y, z) {
        this->color = color;
    }

    string getColor() { return color; }
    void setColor(string color) { this->color = color; }

    void print() {
        cout << "Point3DColor: x=" << x
            << ", y=" << y
            << ", z=" << z
            << ", color=" << color << endl;
    }
};

int main() {
    Point p(1, 2);
    p.print();

    Point3D p3(3, 4, 5);
    p3.print();

    PointColor pc(6, 7, "red");
    pc.print();

    Point3DColor p3c(8, 9, 10, "blue");
    p3c.print();

    return 0;
}
