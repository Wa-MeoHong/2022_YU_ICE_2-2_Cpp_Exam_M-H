/*
  ���ϸ� : "Exam2A_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Class Mtrx, Class MtrxArray�� �����Ͽ�, ������ �����ε��� ���� ����� �������� ����ϴ� �˰���
	- ���, �Ǽ� ������ �ܼ��� ��� ��ҿ� �Ǽ��� ��Ģ������
	- ���, ��� ������ ������ ��Ŀ����� �����

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 21��)
  ���� Update : Version 1.0.0, 2022�� 10�� 21��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/21		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Class_Mtrx.h"
#include "Class_MtrxArray.h"

#define INPUT "Matrix_data.txt"
#define OUTPUT "output.txt"
#define NUM_MTRX 10

int main(void)
{
	ifstream fin;
	ofstream fout;

	fin.open(INPUT);		// Matrix_data.txt ����
	if (fin.fail())
	{
		// ������ ���� ���ϸ� ������ ��
		cout << "Error in opening Matrix_data.txt !!";
		exit(-1);
	}

	fout.open(OUTPUT);		// Matrix_data.txt ����
	if (fout.fail())
	{
		// ������ ���� ���ϸ� ������ ��
		cout << "Error in opening output.txt !!";
		exit(-1);
	}

	// MtrxArray ����
	MtrxArray mtrx(NUM_MTRX);

	// ���� �Է� (���ʴ�� ��), ���� �̸�����
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	mtrx[0].NameSetting("mtrx[0]");
	mtrx[1].NameSetting("mtrx[1]");
	mtrx[2].NameSetting("mtrx[2]");

	// �ܼ����, �������
	cout << mtrx[0]; fout << mtrx[0];
	cout << mtrx[1]; fout << mtrx[1];
	cout << mtrx[2]; fout << mtrx[2];

	// ��Ŀ� �������� ( ����, ����, ����)
	
	// ���[0] + 2.0 ( ����ҿ� ���� ����)
	mtrx[3] = mtrx[0] + 2.0;
	mtrx[3].NameSetting("mtrx[3] = mtrx[0] + 2.0");
	cout << mtrx[3]; fout << mtrx[3];			// ���

	// ���[0] - 2.0 ( ����ҿ� ���� �M)
	mtrx[4] = mtrx[0] - 2.0;					
	mtrx[4].NameSetting("mtrx[4] = mtrx[0] - 2.0");
	cout << mtrx[4]; fout << mtrx[4];			// ���

	// ���[0] * 2.0 ( ����ҿ� ���� ����)
	mtrx[5] = mtrx[0] * 2.0;
	mtrx[5].NameSetting("mtrx[5] = mtrx[0] * 2.0");
	cout << mtrx[5]; fout << mtrx[5];			// ���

	// ���[0] + ���[1] (��ĵ���)
	mtrx[6] = mtrx[0] + mtrx[1];
	mtrx[6].NameSetting("mtrx[6] = mtrx[0] + mtrx[1]");
	cout << mtrx[6]; fout << mtrx[6];			// ���

	// ���[0] - ���[1] (��Ļ���)
	mtrx[7] = mtrx[0] - mtrx[1];
	mtrx[7].NameSetting("mtrx[7] = mtrx[0] - mtrx[1]");
	cout << mtrx[7]; fout << mtrx[7];			// ���

	// ���[0] - ���[2] (��İ���)
	mtrx[8] = mtrx[0] * mtrx[2];
	mtrx[8].NameSetting("mtrx[3] = mtrx[0] * mtrx[2]");
	cout << mtrx[8]; fout << mtrx[8];			// ���

	// ~���[0] (��ġ���)
	mtrx[9] = ~mtrx[0];
	mtrx[9].NameSetting("mtrx[9] = transposed(mtrx[0])");
	cout << mtrx[9]; fout << mtrx[9];			// ���



	return 0;
}