#ifndef MTRXARRAY_H
#define MTRXARRAY_H

#include "Class_Mtrx.h"
#include <iostream>

using namespace std;

class MtrxArray						// ��� �迭 Ŭ����
{
public:
	MtrxArray(int array_size);		// ��� �迭 ������ 
	~MtrxArray();					// ��� �迭 �Ҹ���
	Mtrx& operator[](int);			// ��� ��ȯ
	int ArraySize();				// �迭�� ũ�� ��ȯ

private:
	Mtrx* pMtrx;					// ��� �迭 ��� ������
	int mtrxArraySIZE;				// �迭�� ũ��
	bool isValidIndex(int index);	// ��� �ε��� ��ȣ ��ȿ�� �˻�
};

#endif