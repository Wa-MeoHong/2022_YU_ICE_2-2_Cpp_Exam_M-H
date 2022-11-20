/*
  ���ϸ� : "Exam3C_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	-
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 19��)
  ���� Update : Version 1.0.0, 2022�� 11�� 19��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/19		v1.0.0		  �����ۼ�

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

	if (fin.fail())					// ������ �����������ϸ� ��
	{
		cout << "Error! does not open input_data.txt!\n";
		exit(-1);
	}

	fin >> *pnum_date;						// num Date �޾ƿ�
	pData = new int[*pnum_date];

	for (int i = 0; i < *pnum_date; i++)
	{
		fin >> pData[i];					// �Է�
	}
	fin.close();
	return pData;						// ��ȯ
}

int main(void)
{
	int* data_array;
	int num_data;

	data_array = fGetData(INPUT, &num_data);		// ������ �ܾ��

	T_BSTN<int>* pRoot, ** ppBST_int_root;
	T_BST<int> BST_int_noBalancing("BST_int_noBalancing");
	cout << "Testing Binary Search Tree without Rebalancing" << endl;
	for (int i = 0; i < num_data; i++)
	{
		BST_int_noBalancing.insertinOrder(data_array[i]);		// �뷱������ �ʰ� ����
	}
	BST_int_noBalancing.print_with_Depth(cout);				// ���
	cout << "Elements in " << BST_int_noBalancing.Name() << " (in order) : ";
	BST_int_noBalancing.print_inOrder(cout);				// ��� (�������)
	cout << endl;

	T_BST<int> BST_int_Balancing("BST_int_withBalancing");
	cout << "\nTesting Binary Search Tree with Rebalancing" << endl;
	for (int i = 0; i < num_data; i++)
	{
		BST_int_Balancing.insertAndReBal(data_array[i]);		// ���뷱���� �ϸ鼭 ����
	}
	BST_int_Balancing.print_with_Depth(cout );
	cout << "Elements in " << BST_int_Balancing.Name() << " (in order) : ";
	BST_int_Balancing.print_inOrder(cout);			// ���
	cout << endl;

	return 0;
}