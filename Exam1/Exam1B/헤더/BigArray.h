#ifndef BIG_ARRAY_H
#pragma warning(disable: 4996)					// ���� �ȶ߰� �ϴ� pragma����

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef struct ArrayStatistics {
	int min;					// �ּҰ�
	int max;					// �ִ밪
	double avg;					// ���
	double var;					// �л�
	double std_dev;				// ǥ������
}Statistics;

class BigArray
{
public:
	BigArray(int n);			// constructor (������)
	~BigArray();				// destructor (�Ҹ���)
	void genBigRandArray(int size, int offset);		// BigRand �迭�� �����ϴ� �Լ�
	int size() { return array_size; }				// �迭�� ũ�� ��ȯ
	void suffle();									// �迭 ����
	void selection_sort();							// �迭 ��������
	void quick_sort();								// �迭 ������
	void getStatistics();							// �迭 ������ ���
	void fprintStatistics(ostream& fout);			// �迭 ������ ����� ���
	void fprintBigArray(ostream& fout, int num_per_line, int num_lines);		// �迭 ���� ���

private:
	int* big_array = NULL;				// ������ ���� big_array
	int array_size = 0;					// ������ �迭 ������
	Statistics stats;			// �迭�� ������ ��� ����ü
};

#endif