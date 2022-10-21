#include "Cmplx.h"

Cmplx::Cmplx()											// ���Ҽ� ������ 
{
	// ������ �Ǽ��κ�, ����κ��� 0���� �ʱ�ȭ
	real = 0;
	imag = 0;
}

void Cmplx::inputCmplx()								// ���Ҽ� �Է� �Լ�
{
	cout << "input Cmplx.real and Cmplx.imag : ";
	cout << "real : ";
	cin >> real;										// �Ǽ��κ� �Է�
	cout << "imagine : ";
	cin >> imag;										// ����κ� �Է�
}

void Cmplx::printCmplx()								// ���Ҽ� ���
{
	// cout ������� ���� (�Ҽ��� 2�ڸ��� ���)
	cout.setf(ios::fixed);  cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "(" << real << " ";								// �Ǽ��κ� ���
	if (imag < 0)
		cout << "-j" << -(imag) << ")";						// ���� ����κ��� -�� ���, -j�� ���
	else
		cout << "+j" << imag << ")";							// �ƴϸ� �������
}
const Cmplx Cmplx::addCmplx(const Cmplx& c2)			// ���Ҽ� ����
{
	Cmplx result;

	// (a + jb) + (c + jd) = (a + b) + j(c + d) 

	result.real = real + c2.real;						// �Ǽ��κ� ����
	result.imag = imag + c2.imag;						// ����κ� ����

	return result;
}


const Cmplx Cmplx::subCmplx(const Cmplx& c2)			// ���Ҽ� ����
{
	Cmplx result;

	// (a + jb) - (c + jd) = (a - b) + j(c - d) 

	result.real = real - c2.real;						// �Ǽ��κ� �E��
	result.imag = imag - c2.imag;						// ����κ� �E��
		
	return result;
}

const Cmplx Cmplx::mulCmplx(const Cmplx& c2)			// ���Ҽ� ����
{
	Cmplx result;

	// (a + jb)(c + jd) = (ac - bd) + j(bc + ad) (������ ���� �̿�)

	result.real = (real * c2.real) - (imag * c2.imag);	// �Ǽ��κ� ����
	result.imag = (real * c2.imag) + (imag * c2.real);	// ����κ� ����

	return result;
}

const Cmplx Cmplx::divCmplx(const Cmplx& c2)
{
	Cmplx result;
	double denom;

	// (a + jb) / (c + jd) = ((ac + bd)/(c�� + d��)) + j((bc - ad)/(c�� + d��)) (��� �� ������ ���� �̿�)

	denom = pow(c2.real, 2) + pow(c2.imag, 2);							// (c�� + d��)		

	result.real = ((real * c2.real) + (imag * c2.imag)) / denom;		// �Ǽ��κ� ������ ���
	result.imag = ((imag * c2.real) - (real * c2.imag)) / denom;		// ����κ� ������

	return result;
}



