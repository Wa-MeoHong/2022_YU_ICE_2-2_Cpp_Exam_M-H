#include "Mtrx.h"

/*				constructor (������)
	1. ��(num_row), ��(num_col)�� �˰��ִ� ���¿��� ����� ���( �����ʹ� 0.0���� �ʱ�ȭ )
	2. ���� ��, �����͸� ��� ���Ͽ��� �޾ƿͼ� ����� ���
															*/
Mtrx::Mtrx(int num_row, int num_col)
{
	n_row = num_row;						// �� ����
	n_col = num_col;						// �� ����
	dMtrx = new double* [n_row];				// new �����ڸ� ���� double* ���� �迭 ���� ( ���Ұ����� n_row�� ��ŭ )
	for (int i = 0; i < n_row; i++)			// new �����ڸ� ���� double ���� �迭 ���� ( �迭�� n_col�� ��ŭ)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// ���� ������ ( 0.0���� )
	{
		for (int k = 0; k < n_col; k++)
		{
			dMtrx[j][k] = 0.0;
		}
	}

}
Mtrx::Mtrx(ifstream& fin)
{
	fin >> n_row >> n_col;					// ���� ���� �����͸� ���Ͽ��� �о��

	dMtrx = new double* [n_row];			// new �����ڸ� ���� double* ���� �迭 ���� ( ���Ұ����� n_row�� ��ŭ )
	for (int i = 0; i < n_row; i++)			// new �����ڸ� ���� double ���� �迭 ���� ( �迭�� n_col�� ��ŭ)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// ���Ϸκ��� �����͸� �о��
	{
		for (int k = 0; k < n_col; k++)
		{
			if (fin.eof())
				dMtrx[j][k] = 0.0;			// ���� ���Ͽ��� �����͸� ��� �о����� �ʱⰪ ������ �ȳ����ٸ� 0.0���� 
			else {
				fin >> dMtrx[j][k];			// ���Ͼּ� �����͸� �о�� �迭�� ����
			}
		}
	}
}

/*				 distructor (�Ҹ���)					*/
Mtrx::~Mtrx()
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete �����ڸ� ���� �����Ҵ��� �迭�� ����
	//}
	//delete[] dMtrx;							// ���ѹ� delete�� ���� �����Ҵ� ����
}

/*				 ��� ���� ���� ���
	1. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���)
	2. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���)
	3. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���)
	5. ��� ���� �ִ�, �ּҰ� ���
												*/
Mtrx Mtrx::addMtrx(const Mtrx& mM)								// ��� ����
{
	Mtrx mR(n_row, n_col);										// ��� ��� ����
	mR.NameSetting("Add Mtrx");									// �̸� ����

	for (int i = 0; i < n_row; i++)								// ��� ���� ����
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;													// ��� ��ȯ
}
Mtrx Mtrx::subMtrx(const Mtrx& mM)								// ��� ����
{
	Mtrx mR(n_row, n_col);										// ��� ��� ����
	mR.NameSetting("Sub Mtrx");

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] - mM.dMtrx[i][j];
	}

	return mR;
}
Mtrx Mtrx::mulMtrx(const Mtrx& mM)							// ��� ���� �Լ�
{
	int row_SIZE, col_SIZE, SIZE_k;

	row_SIZE = n_row; col_SIZE = mM.col(); SIZE_k = mM.row();	// ����� ��� ����� ��, �������� 
	Mtrx mR(row_SIZE, col_SIZE);							// ��, �� �����͸� ������ ��� ����
	mR.NameSetting("Mul Mtrx");								// �̸� ����

	for (int i = 0; i < row_SIZE; i++)						// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)					// �� ��ȯ
		{
			for (int k = 0; k < SIZE_k; k++)				// �μ��� ���Ѱ͵� �����ϱ�
			{
				mR.dMtrx[i][j] += dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}

/*					��� ��� �Լ�					*/
void Mtrx::fprintMtrx(ofstream& fout)						// ���� ����Լ�
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )

	fout << name << " = " << endl;
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{

			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				fout << a6 << a3;										// ��
			else if (i > 0 && i < n_row - 1 && k == 0)
				fout << a6 << a2;										// ��
			else if (i == n_row - 1 && k == 0)
				fout << a6 << a6;										// ��

			fout.setf(ios::fixed);  fout.setf(ios::showpoint);
			fout << setw(7); fout.precision(2);
			fout << dMtrx[i][k];						// ���� ��ºκ�


			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == n_col - 1)
				fout << a6 << a4;										// ��
			else if (i > 0 && i < n_row - 1 && k == n_col - 1)
				fout << a6 << a2;										// ��
			else if (i == n_row - 1 && k == n_col - 1)
				fout << a6 << a5;										// ��
		}
		fout << endl;
	}
	fout << endl;

}
