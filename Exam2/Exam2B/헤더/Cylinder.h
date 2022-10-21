#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include "Shape.h"
#include "Circle.h"

using namespace std;

class Cylinder : public Circle
{
	friend ostream& operator<< (ostream&, const Cylinder&);
public:
	// constructor, destuctor
	Cylinder();
	Cylinder(string n) : Circle(n), height(0) {};
	Cylinder(string n, int r, int h);
	Cylinder(const Cylinder& cyl);
	virtual ~Cylinder();

	//member functions
	virtual void print(ostream&) const;					// ���� ��� ) 

	//getter
	int Height() const { return height; }				// ����
	double Sur_Area() const;							// ����
	double Volume() const;

	//setter 
	void Set_Height(int h) { height = h; }				// ������ ����

	// operator Overloading
	Cylinder& operator=(const Cylinder& cyl);

protected:
	int height;
};



#endif // !CYLINDER_H
