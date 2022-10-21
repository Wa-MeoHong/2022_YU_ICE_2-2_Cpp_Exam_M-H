#ifndef CMPLX_H
#define CMPLX_H
#pragma warning(disable: 4996)					// ���� �ȶ߰� �ϴ� pragma����

#include <iostream>

using namespace std;

class Cmplx										// ���Ҽ� Ŭ����
{
public:
	Cmplx();									// constructor (������)
	void inputCmplx();							// ���Ҽ� �Է�
	void printCmplx();							// ���Ҽ� ���
	const Cmplx addCmplx(const Cmplx&);			// ���Ҽ� ����
	const Cmplx subCmplx(const Cmplx&);			// ���Ҽ� ����
	const Cmplx mulCmplx(const Cmplx&);			// ���Ҽ� ����
	const Cmplx divCmplx(const Cmplx&);			// ���Ҽ� ������

private:
	double real;								// �Ǽ� �κ�
	double imag;								// ��� �κ�
};



#endif // !CMPLX_H\



