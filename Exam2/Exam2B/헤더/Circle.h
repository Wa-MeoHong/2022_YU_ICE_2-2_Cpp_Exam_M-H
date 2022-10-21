#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "Shape.h"

using namespace std;

class Circle : public Shape
{
	friend ostream& operator<< (ostream&, const Circle&);

public:
	// constructor
	Circle();
	Circle(string name);
	Circle(string name, int r);
	Circle(const Circle& cir);

	// destuctor
	~Circle();

	// member functions
	virtual void print(ostream&) const;							// Shape 출력

	// getter
	double Circumference() const;
	double Area() const;
	int Radius() const { return radius; }

	// setter
	void setRadius(int r) { radius = r; }

	// operator Overloading
	Circle& operator=(const Circle& cir);

protected:
	int radius;
};
#endif