#include "BigArray.h"
#include <iostream>
#include <iomanip>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)					// �ִ밪 ã�� ��ũ���Լ�
#define MIN(x, y) ((x) < (y)) ? (x) : (y)					// �ּҰ� ã�� ��ũ���Լ�
#define RANDOMIZE() srand((unsigned int)time(NULL))
#define OFFSET -500000										// offset(���ذ�)
#define BIG_SIZE 500
#define LINESIZE 10

using namespace std;

int _partition(int* array, int SIZE, int left, int right, int PivotIndex);		// pivot�� �������� ���ʿ� ������, �����ʿ� ū������ �����͸� �ű�
void _quickSort(int* array, int SIZE, int left, int right);						// ������ ���Լ�
void suffleArray(int* array, int size);											// ó�� �迭 ������ ��, ��ü�� ����Լ��� �����ؼ� ���� ����

/*						������ �� �Ҹ���						*/
BigArray::BigArray(int n)									// ������
{
	array_size = n;											// ���� n���� ����
	memset(&stats, 0, sizeof(Statistics));					// ����ü���� �ʱ�ȭ
}
BigArray::~BigArray()										// �Ҹ���
{
	cout << "distructed Array" << endl;
	if (big_array != NULL)
		delete[] big_array;
}

/*						�迭 ���� ���� �Լ�
		1. �迭 ���� (������� offset �Ű������� ����)
		2. suffleArray( genBigRandArray ���� )
		3. Ŭ���� ��ü�� ����ϴ� suffle �Լ�					*/
void BigArray::genBigRandArray(int size, int offset)			// ���� ���� �Լ�
{
	RANDOMIZE();												// ���� �õ� ����

	big_array = new int[size];				// array_size(������ ������ �� ����)��ŭ �����Ҵ� 

	/*
				>> �ߺ��� ���� ������ ���� �����ϱ� ������ �̷� ��ĵ� ���� <<
		1. for���� ���� 0 ~ ������ �� ���� 1���� ���ʴ�� �迭�� �������
		2. �� ��, suffle�� ���� ������ �������
	*/
	for (int i = 0; i < size; i++)
	{
		big_array[i] = i + offset;
	}
	suffleArray(big_array, size);
}
void suffleArray(int* array, int size)
{
	int i1, i2, temp, i = 0;

	while (i != size)										// i�� ���� ��������
	{
		// �ٲ� ���ڸ� 2�� ������. ������ RAND�Լ��� ����
		i1 = (((unsigned int)rand() << 15) | rand()) % size;
		i2 = (((unsigned int)rand() << 15) | rand()) % size;

		// swapping, �ٲܶ��� temp���� �� ���� �ϳ��� �ʿ���
		temp = array[i1];
		array[i1] = array[i2];
		array[i2] = temp;

		i++;													// i ����
	}

}
void BigArray::suffle()								// �����ֱ� (����) �Լ�
{
	int i1, i2, temp, i = 0;

	while (i != array_size)										// i�� ���� ��������
	{
		// �ٲ� ���ڸ� 2�� ������. ������ RAND�Լ��� ����
		i1 = (((unsigned int)rand() << 15) | rand()) % array_size;
		i2 = (((unsigned int)rand() << 15) | rand()) % array_size;

		// swapping, �ٲܶ��� temp���� �� ���� �ϳ��� �ʿ���
		temp = big_array[i1];
		big_array[i1] = big_array[i2];
		big_array[i2] = temp;

		i++;													// i ����
	}
}

/*						�迭 ���� ���� �Լ�
		1. �������� (Selection Sort)
		2. ������ (Quick Sort)
		3. ������ ��, Pivot�������� ������, ū������ �з��ϴ� �Լ�
		4. ������ �� �Լ�										*/
void BigArray::selection_sort()								// ��������
{
	int min_NUM;											// ������ ã��
	int Index_min_NUM;										// �������� �ε��� �ѹ�

	for (int round = 0; round < array_size - 1; round++)
	{
		Index_min_NUM = round;								// �ּҰ��� �ε��� �ʱⰪ(round) ����
		min_NUM = big_array[round];							// �ּҰ� �ʱⰪ ����
		for (int i = round + 1; i < array_size; i++)
		{
			if (big_array[i] < min_NUM)
			{
				Index_min_NUM = i;
				min_NUM = big_array[i];
			}
		}
		if (Index_min_NUM != round)						// ���� ���� ���� ���� �ڱ��ڽ�(���ذ�)�� �ƴ϶��
		{
			big_array[Index_min_NUM] = big_array[round];		// ã�Ҵ� �ε��� �ּҾ��� ���� ���ذ��� ����
			big_array[round] = min_NUM;						// ������������ �Ʊ� �����ߴ� �� ������.
		}
	}

}
void BigArray::quick_sort()
{
	_quickSort(big_array, array_size, 0, array_size - 1);
}
int _partition(int* array, int SIZE, int left, int right, int PivotIndex)
{
	int PivotValue, newPI;
	double temp;

	PivotValue = array[PivotIndex];
	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// �� ó�� PivotIndex�� �ִ� ���� �� ������(Ȥ�� P_I-1��ġ�� �ִ� ��)�� �ٲ۴�

	newPI = left;						// ���� ���ο� �ǹ���ġ�� �������ִµ� �ʱⰪ�� �� ����(Ȥ�� P_I + 1��ġ)���� ����
	for (int i = left; i <= right - 1; i++)
		// �ǵڷ� ���Ե� PivotValue�� ���� ������ �迭���� ������ ��´�.
	{
		if (array[i] <= PivotValue)								//���� �ǵڷ� �� PivotValue���� ���� �۴ٸ�
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;							// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
			newPI += 1;
		}
	}
	// ��������� ó�� PivotValue���� �������� ������ PivotValue���� ���� ������ �迭, �������� PivotValue���� ū ������ �迭�� �����Ǿ���.
	PivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = PivotValue;

	return newPI;											// newPI ��ȯ
}
void _quickSort(int* array, int SIZE, int left, int right)
{
	int P_I, newPI;

	if (left >= right)					// ���� left�� right���� ũ�ų� ���ٸ� newPI��ȯ ����, ���� left�� 1Ȥ�� 0�϶��̴�..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;							// �߰���, ���� Ȧ���ΰ�� ���������� ��������ġ�� ����
	}

	newPI = _partition(array, SIZE, left, right, P_I);


	// �̷��� ����, ������ ������� �������� �� ū����
	if (left < (newPI - 1))									// ���� newPI�������� ���ʺκ�
	{
		_quickSort(array, SIZE, left, newPI - 1);
		// �ٽ� newPI�� �����ϸ鼭 ũ�������� �����ش�.
	}
	if ((newPI + 1) < right)								// ����, ������ quickSort�� ������, newPI���� ������ �κ�
	{
		_quickSort(array, SIZE, newPI + 1, right);
		// ���������� newPI����� ũ������� �������ش�.
	}
}

/*						�迭 ������ �� ��� ���� �Լ�
		1. �迭 �������� �������� ����
		2. �迭 ������ ������ ��� �Լ�
		3. �迭 ��� �Լ�										*/
void BigArray::getStatistics()
{
	double sum = 0; int max = big_array[0], min = big_array[0];		// min, max, sum ���� ����
	double pow_sum = 0;												// ���������� ��

	for (int i = 0; i < array_size; i++)
	{
		sum += big_array[i];							// ��� ���� ����
		max = MAX(max, big_array[i]);					// �� �� �ִ밪 ����
		min = MIN(min, big_array[i]);					// �� �� �ּҰ� ����
	}
	stats.min = min; stats.max = max;					// stats ����ü�� ����
	stats.avg = sum / array_size;						// stats ����ü�� ��� ����

	
	for (int j = 0; j < array_size; j++)
		pow_sum += pow(big_array[j], 2);				// ������ ���� ����
	stats.var = (pow_sum / array_size) - pow(stats.avg, 2);					// �л� = ������ ��� - ����� ����
	stats.std_dev = sqrt(stats.var);					// ǥ������ - ��л�
}
void BigArray::fprintStatistics(ostream& fout)			// ��� ��� �������
{
	fout.setf(ios::fixed); fout.setf(ios::showpoint); fout.precision(2);
	// fout�� ��� ���� �ڸ����� ���� ����
	getStatistics();							// �������� ����
	// ���
	fout << "Statistics : " << endl;
	fout << " min (" << stats.min << "), max (" << stats.max <<
		"), avg (" << stats.avg << "), var (" << stats.var <<
		"), std_dev (" << stats.std_dev << ")" << endl;
}
void BigArray::fprintBigArray(ostream& fout, int num_per_line, int num_lines)	// ���� ��� �Լ�
{
	int count = 0;												// ����� �� �ʿ���

	int lines = num_lines;
	/*				>>> ��� ��� <<<
		1. array_size(������ ����)�� ���� ��¹���� �����Ѵ�.
		2. BIG_SIZE���� ���� ���, �������� ���
		3. BIG_SIZE���� ���� ���, ó�� 50�� ����ϰ� ���� �߰� ���� ��, ���� �ѹ��� 50�� ���
	*/

	if (array_size < BIG_SIZE)
	{
		lines = array_size / num_per_line;
	}

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < num_per_line; j++)
		{
			if (count == array_size)							// ���� ��������� Ż��
				break;
			fout << setw(9) << big_array[count];				// ���, �ڸ����� 7�� ������, 7�ڸ�
			count++;
		}
		fout << endl;											// 10�� ��� �� ����
	}

	// ������ ���� BIG_SIZE���� �� ū ���, ���� ��, ����Ѵ�.
	if (array_size >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// �����ϴ� ��
		count = array_size - (num_per_line * num_lines);

		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < num_per_line; j++)
			{
				fout << setw(9) << big_array[count];			// ���
				count++;
			}
			fout << endl;										// ���� ����
		}
		fout << endl;
	}
}
