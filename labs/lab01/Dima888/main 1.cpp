#include <iostream>
#include "Point .cpp"
//ствоити клас  point, point 3d, point color, point 3d color, set get print  

int main()
{
	Point p1(10, 20);
	p1.print();

	Point3D p2(10, 20, 30);
	p2.setZ(100);
	p2.print();

	PointColor p3(8, 8, "Pink");
	p3.print();

	Point3DColor p4(6, 9, 7, "Black");
	p4.setColor("Purple");
	p4.print();

}


