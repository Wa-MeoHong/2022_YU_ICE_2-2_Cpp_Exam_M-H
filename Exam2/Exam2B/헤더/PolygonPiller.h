#ifndef PolyCYLINDER_H
#define PolyCYLINDER_H

#include <iostream>
#include "Shape.h"
#include "Polygon.h"

using namespace std;

class PolygonPiller : public PolyGon
{
	friend ostream& operator<< (ostream&, const PolygonPiller&);
public:
	// constructor, destuctor
	PolygonPiller();
	PolygonPiller(string n) : PolyGon (n), height(0) {};
	PolygonPiller(string n, int r, int num_poly, int h);
	PolygonPiller(const PolygonPiller& cyl);
	virtual ~PolygonPiller();

	//member functions
	virtual void print(ostream&) const;					// 정보 출력 ) 

	//getter
	int Height() const { return height; }				// 높이
	double Sur_Area() const;							// 넓이
	double Volume() const;

	//setter 
	void Set_Height(int h) { height = h; }				// 반지름 대입

	// operator Overloading
	PolygonPiller& operator=(const PolygonPiller& cyl);

protected:
	int height;
};



#endif // !CYLINDER_H
