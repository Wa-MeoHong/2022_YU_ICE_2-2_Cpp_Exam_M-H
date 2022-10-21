#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;
#define PI 3.14159265358979323846			// pi

class Shape									// Shape Ŭ���� ( ��� ) 
{
	friend ostream& operator<<(ostream& out, const Shape s);
public:
	// constructor
	Shape();
	Shape(string name);
	// destuctor
	virtual ~Shape();

	//member functions
	//virtual void draw();									// ���� �׸��� �Լ�
	//virtual void draw(ConsolePixelFrame cp_frame);			// ����
	virtual void print(ostream&) const;							// Shape ��ü ���

	//getter
	string Name() const { return name; }	// �̸�
	//setter 
	void NameSet(string n) { name = n; }	// �̸� ����

	// operator Overloading
	Shape& operator=(const Shape& s);

protected:
	string name;							// �̸�
};

#endif // !SHAPE_H