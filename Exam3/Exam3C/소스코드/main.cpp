/*
  파일명 : "Exam3C_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	-
  프로그램 작성자 : 신대홍(2022년 11월 19일)
  최종 Update : Version 1.0.0, 2022년 11월 19일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/19		v1.0.0		  최초작성

===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "T_BST.h"

using namespace std;

#define INPUT "input_data.txt"
#define OUTPUT "output.txt"

int* fGetData(string Fin_name, int* pnum_date)
{
	ifstream fin(INPUT);
	int* pData = NULL;

	if (fin.fail())					// 파일을 오픈하지못하면 끝
	{
		cout << "Error! does not open input_data.txt!\n";
		exit(-1);
	}

	fin >> *pnum_date;						// num Date 받아옴
	pData = new int[*pnum_date];

	for (int i = 0; i < *pnum_date; i++)
	{
		fin >> pData[i];					// 입력
	}
	fin.close();
	return pData;						// 반환
}

int main(void)
{
	int* data_array;
	int num_data;

	data_array = fGetData(INPUT, &num_data);		// 데이터 긁어옴

	T_BSTN<int>* pRoot, ** ppBST_int_root;
	T_BST<int> BST_int_noBalancing("BST_int_noBalancing");
	cout << "Testing Binary Search Tree without Rebalancing" << endl;
	for (int i = 0; i < num_data; i++)
	{
		BST_int_noBalancing.insertinOrder(data_array[i]);		// 밸런싱하지 않고 삽입
	}
	BST_int_noBalancing.print_with_Depth(cout);				// 출력
	cout << "Elements in " << BST_int_noBalancing.Name() << " (in order) : ";
	BST_int_noBalancing.print_inOrder(cout);				// 출력 (순서대로)
	cout << endl;

	T_BST<int> BST_int_Balancing("BST_int_withBalancing");
	cout << "\nTesting Binary Search Tree with Rebalancing" << endl;
	for (int i = 0; i < num_data; i++)
	{
		BST_int_Balancing.insertAndReBal(data_array[i]);		// 리밸런싱을 하면서 삽입
	}
	BST_int_Balancing.print_with_Depth(cout );
	cout << "Elements in " << BST_int_Balancing.Name() << " (in order) : ";
	BST_int_Balancing.print_inOrder(cout);			// 출력
	cout << endl;

	return 0;
}