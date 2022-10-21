#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include "Shape.h"

using namespace std;

class PolyGon : public Shape
{
	friend ostream& operator<< (ostream&, const PolyGon&);

public:
	// constructor
	PolyGon();
	PolyGon(string name);
	PolyGon(string name, int r, int n_poly);
	PolyGon(const PolyGon& poly);

	// destuctor
	~PolyGon();

	//member functions
	virtual void print(ostream&) const;							// Shape 도형 반환
	double get_base_length() const;
	double get_perimeter() const;
	double Area() const ;
	double Volume() { return 0.0; }

	//getter
	int Radius() const { return radius; }
	int NumPoly() const { return num_poly; }

	// setter
	void setRadius(int r) { radius = r; }
	void setNumPoly(int n_poly) { num_poly = n_poly; }

	// operator Overloading
	PolyGon& operator=(const PolyGon& poly);

protected:
	int radius;
	int num_poly;
};

#endif // !POLYGON_H