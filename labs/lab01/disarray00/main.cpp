#include <iostream>
#include <string>

class Point {
private:
  int x, y;

public:
  Point() : x(0), y(0) {}

  Point(int px, int py) : x(px), y(py) {}

  Point(const Point &oth) : x(oth.getX()), y(oth.getY()) {}

  int getX() const { return x; }
  int getY() const { return y; }

  void setX(int px) { x = px; }
  void setY(int py) { y = py; }

  virtual void print() { std::cout << x << ", " << y << '\n'; }
};

class Point3D : virtual public Point {
private:
  int z;

public:
  Point3D() : Point(), z(0) {}

  Point3D(int px, int py, int pz) : Point(px, py), z(pz) {}

  Point3D(const Point3D &oth) : Point(oth), z(oth.getZ()) {}

  int getZ() const { return z; }

  void setZ(int pz) { z = pz; }

  void print() override {
    std::cout << getX() << ", " << getY() << ", " << getZ() << '\n';
  }
};

class PointColor : virtual public Point {
private:
  std::string color;

public:
  PointColor() : Point(), color("yellow") {}

  PointColor(int px, int py, std::string col = "yellow")
      : Point(px, py), color(col) {}

  PointColor(const PointColor &oth) : Point(oth), color(oth.getColor()) {}

  std::string getColor() const { return color; }

  void setColor(std::string col) { color = col; }

  void print() override {
    std::cout << getX() << ", " << getY() << " : " << getColor() << '\n';
  }
};

class Point3DColor : public Point3D, public PointColor {
public:
  Point3DColor() : Point(), Point3D(), PointColor() {}

  Point3DColor(int px, int py, int pz, std::string col = "yellow")
      : Point(px, py), Point3D(px, py, pz), PointColor(px, py, col) {}

  Point3DColor(const Point3DColor &oth)
      : Point(oth), Point3D(oth), PointColor(oth) {}

  void print() override {
    std::cout << getX() << ", " << getY() << ", " << getZ() << " : "
              << getColor() << '\n';
  }
};

int main() {
  Point a;
  Point3D b(3, 7, 2);
  PointColor c(5, 1, "red");
  Point3DColor d(4, 6, 8, "blue");

  a.print();
  b.print();
  c.print();
  d.print();

  b.setZ(11);
  c.setColor("green");

  b.print();
  c.print();

  Point3DColor e(d);
  e.print();

  return 0;
}
