/*
  ���ϸ� : "Exam1C_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Class Mtrx (��� Ŭ����)�� ����� ����� �ϴ� ���α׷�
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
#include <iomanip>
#include <fstream>
#include "Mtrx.h"

#define INPUT "Matrix_data.txt"				// �Է����� "Matrix_date.txt"
#define OUTPUT "output.txt"					// ������� "output.txt"

using namespace std;

int main(void)
{
	ifstream fin;							// �Է¿� ����
	ofstream fout;							// ��¿� ����

	// ���� ���� ��, ������ ����� ��� ����
	fin.open(INPUT); fout.open(OUTPUT);
	if (fin.fail())
	{
		cout << "Error in opening Matrix_data.txt!!" << endl; exit(-1);
	}
	if (fout.fail())
	{
		cout << "Error in opening output.txt!!" << endl; exit(-1);
	}

	Mtrx mtrxA(fin);						// ��� A ����
	mtrxA.NameSetting("mtrxA");				// �̸� ����
	mtrxA.fprintMtrx(fout);					// ���

	// ��� B ���� �� ���
	Mtrx mtrxB(fin);
	mtrxB.NameSetting("mtrxB");
	mtrxB.fprintMtrx(fout);

	// ��� C ���� �� ���
	Mtrx mtrxC(fin);
	mtrxC.NameSetting("mtrxC");
	mtrxC.fprintMtrx(fout);

	// ��� D ( ��� A + ��� B ) ���� �� ���
	Mtrx mtrxD(mtrxA.row(), mtrxB.col());
	mtrxD = mtrxA.addMtrx(mtrxB);
	mtrxD.NameSetting("mtrxD = mtrxA.add(mtrxB)");
	mtrxD.fprintMtrx(fout);

	// ��� E ( ��� A - ��� B ) ���� �� ���
	Mtrx mtrxE(mtrxA.row(), mtrxB.col());
	mtrxE = mtrxA.subMtrx(mtrxB);
	mtrxE.NameSetting("mtrxE = mtrxA.sub(mtrxB)");
	mtrxE.fprintMtrx(fout);

	// ��� F ( ��� A * ��� C ) ���� �� ���
	Mtrx mtrxF(mtrxA.row(), mtrxC.col());
	mtrxF = mtrxA.mulMtrx(mtrxC);
	mtrxF.NameSetting("mtrxF = mtrxA.multiply(mtrxC)");
	mtrxF.fprintMtrx(fout);

	// ���� �ݱ�
	fin.close();
	fout.close();

	return 0;
}