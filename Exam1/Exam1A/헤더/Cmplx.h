#ifndef CMPLX_H
#define CMPLX_H
#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의

#include <iostream>

using namespace std;

class Cmplx										// 복소수 클래스
{
public:
	Cmplx();									// constructor (생성자)
	void inputCmplx();							// 복소수 입력
	void printCmplx();							// 복소수 출력
	const Cmplx addCmplx(const Cmplx&);			// 복소수 덧셈
	const Cmplx subCmplx(const Cmplx&);			// 복소수 뺄셈
	const Cmplx mulCmplx(const Cmplx&);			// 복소수 곱셈
	const Cmplx divCmplx(const Cmplx&);			// 복소수 나눗셈

private:
	double real;								// 실수 부분
	double imag;								// 허수 부분
};



#endif // !CMPLX_H\



