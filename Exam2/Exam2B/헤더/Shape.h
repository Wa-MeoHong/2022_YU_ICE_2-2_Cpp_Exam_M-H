#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;
#define PI 3.14159265358979323846			// pi

class Shape									// Shape 클래스 ( 모양 ) 
{
	friend ostream& operator<<(ostream& out, const Shape s);
public:
	// constructor
	Shape();
	Shape(string name);
	// destuctor
	virtual ~Shape();

	//member functions
	//virtual void draw();									// 도형 그리기 함수
	//virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	virtual void print(ostream&) const;							// Shape 객체 출력

	//getter
	string Name() const { return name; }	// 이름
	//setter 
	void NameSet(string n) { name = n; }	// 이름 설정

	// operator Overloading
	Shape& operator=(const Shape& s);

protected:
	string name;							// 이름
};

#endif // !SHAPE_H