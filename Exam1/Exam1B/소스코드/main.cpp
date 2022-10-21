/*
  ���ϸ� : "Exam1B_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- BigArray Ŭ������ ����� ����ϴ� ���α׷�
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 9�� 23��)
  ���� Update : Version 1.0.0, 2022�� 9�� 23��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/09/23		v1.0.0		  �����ۼ�

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "BigArray.h"

using namespace std;

#define ELEMENTS_PER_LINE 10					// ���ٴ� ����ϴ� �μ��� ����
#define SAMPLE_LINES 3							// �߰� ������ ����ϴ� ���� ����
#define OUTPUT "output.txt"

int main(void)
{
	ofstream fout;
	fout.open(OUTPUT);								// ���� ����
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;	exit;
	}

	/*					�迭 1					*/
	int big_rand_size = 1000;						// �迭 1�� 1000�� ����
	int base_offset = 0;							// ������(������)�� 0����
	BigArray ba_1(big_rand_size);					// �迭����

	// ���Ͽ� �迭1 ���� �� ���
	fout << "Generating big rand array of " << ba_1.size()
		<< " elements with base_offset (" << base_offset << ") ... " << endl;
	ba_1.genBigRandArray(big_rand_size, base_offset);				// ���� �� ����
	ba_1.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// ���Ͽ� ���
	ba_1.fprintStatistics(fout);								// �������� ������ ��� �� ���
	ba_1.selection_sort();										// ��������
	fout << "Sorted big random array :" << endl;				
	ba_1.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// �������ĵ� ������ ���
	cout << "Array 1 print complete!" << endl;

	/*					�迭	 2					*/
	big_rand_size = 10000000;									// 1õ���� ������ ����	
	base_offset = -big_rand_size / 2;							// ������ -500��
	BigArray ba_2(big_rand_size);								// �迭 2 ����
	
	// ���Ͽ� �迭 2���� �� ���
	fout << endl << "Generating big rand array of " << ba_2.size()
		<< " elements with base_offset (" << base_offset << ") ... " << endl;
	ba_2.genBigRandArray(big_rand_size, base_offset);				// �迭 ���ϱ�
	ba_2.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// �迭 ���
	ba_2.fprintStatistics(fout);								// �迭 2 ������ ����� ���
	ba_2.quick_sort();											// ������ ����
	fout << "Sorted big random array :" << endl;
	ba_2.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// �����ĵ� �迭 2 ���
	cout << "Array 2 print complete!" << endl;
	
	fout.close();												// ������� �ݱ�


	return 0;
}