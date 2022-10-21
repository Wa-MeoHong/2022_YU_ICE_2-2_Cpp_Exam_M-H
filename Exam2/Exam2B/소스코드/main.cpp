/*
  ���ϸ� : "Exam2B_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	-  �������  ���
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 21��)
  ���� Update : Version 1.0.0, 2022�� 10�� 21��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/18		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include <iostream>
#include "Circle.h"
#include "Cylinder.h"
#include "PolyGon.h"
#include "PolygonPiller.h"
#include "Shape.h"

#define OUTPUT "output.txt"
#define NUM_SHAPES 10

int main(void)
{
	Circle cir("Circle", 10);
	PolyGon plg_3("Triangle", 10, 3);
	PolyGon plg_4("Square", 10, 4);
	PolyGon plg_5("Pentagon", 10, 5);
	PolyGon plg_6("Hexagon", 10, 6);

	Cylinder cyl("Cylinder", 10, 20);
	PolygonPiller plyPlr_3("Prism", 10, 3, 20);
	PolygonPiller plyPlr_4("Hexahedron", 10, 4, 20);
	PolygonPiller plyPlr_5("PentagonPillar", 10, 5, 20);
	PolygonPiller plyPlr_6("HexagonPillar", 10, 6, 20);

	Shape* shapes[NUM_SHAPES];
	shapes[0] = &cir;
	shapes[1] = &plg_3;
	shapes[2] = &plg_4;
	shapes[3] = &plg_5;
	shapes[4] = &plg_6;
	shapes[5] = &cyl;
	shapes[6] = &plyPlr_3;
	shapes[7] = &plyPlr_4;
	shapes[8] = &plyPlr_5;
	shapes[9] = &plyPlr_6;
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		shapes[i]->print(cout);
		cout << endl;
	}

	return 0;
}