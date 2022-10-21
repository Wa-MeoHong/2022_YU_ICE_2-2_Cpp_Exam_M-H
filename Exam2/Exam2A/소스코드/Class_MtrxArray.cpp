#include "Class_MtrxArray.h"
#include "CLass_Mtrx.h"

/*					������, �Ҹ���				
		1. MtrxArray (������)
		2. ~MtrxArray (�Ҹ���)					*/
MtrxArray::MtrxArray(int array_size)						// ��� �迭 �ʱ� ���� 
{
	mtrxArraySIZE = array_size;								// �迭�� ũ�� 
	pMtrx = new Mtrx[array_size];							// �����Ҵ�
}
MtrxArray::~MtrxArray()										// �迭 �Ҹ���
{
	if (pMtrx != NULL)
	{
		delete[] pMtrx;										// �迭 �����Ҵ� ����
	}
}

/*					member funcitions
		1. subError() ( ���� �ε�����ȣ�� �������� ����ϴ� �Լ�)
		2. ArraySize() ( �迭�� ũ�� ��ȯ)					
		3. isValidIndex(index) ( �ε����� ��ȿ���� ��ȿ���˻� )
		4. operator[](sub) ( �迭�� �ε����� �ִ� �� ��ȯ )*/
void subError()												// ���� ��� �Լ�
{
	cout << "ERROR: Subscript out of range.\n";	exit(0);
}

Mtrx& MtrxArray::operator[](int sub)						// �迭 �ε����� �ҷ����� ������ [] �����ε�
{
	if (isValidIndex(sub))									// �迭 �ε��� ��ȣ�� ��ȿ���� Ȯ��
		return pMtrx[sub];									// ��ȿ�ϸ� �迭�� �ε����� �ش�Ǵ� ������ ��ȯ
	else
		subError();											// �ƴϸ� ���� �޼��� �� ����
}

int MtrxArray::ArraySize()									// �迭�� ũ�� ��ȯ
{
	return mtrxArraySIZE;
}

bool MtrxArray::isValidIndex(int index)						// �迭 �ε��� ��ȿ�� �˻�
{
	if (index < 0 || index >= this->ArraySize())				// �迭�ε��� ��ȣ�� 0���� SIZE-1���̿� �ִ� ��������
		return false;										// �ƴϸ� false, ������ true
	else
		return true;
}