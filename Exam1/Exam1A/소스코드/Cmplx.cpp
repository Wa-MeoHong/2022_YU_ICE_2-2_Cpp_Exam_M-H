#include "Cmplx.h"

Cmplx::Cmplx()											// 복소수 생성자 
{
	// 생성시 실수부분, 허수부분을 0으로 초기화
	real = 0;
	imag = 0;
}

void Cmplx::inputCmplx()								// 복소수 입력 함수
{
	cout << "input Cmplx.real and Cmplx.imag : ";
	cout << "real : ";
	cin >> real;										// 실수부분 입력
	cout << "imagine : ";
	cin >> imag;										// 허수부분 입력
}

void Cmplx::printCmplx()								// 복소수 출력
{
	// cout 출력포맷 변경 (소수점 2자리만 출력)
	cout.setf(ios::fixed);  cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "(" << real << " ";								// 실수부분 출력
	if (imag < 0)
		cout << "-j" << -(imag) << ")";						// 만약 허수부분이 -일 경우, -j를 출력
	else
		cout << "+j" << imag << ")";							// 아니면 정상출력
}
const Cmplx Cmplx::addCmplx(const Cmplx& c2)			// 복소수 덧셈
{
	Cmplx result;

	// (a + jb) + (c + jd) = (a + b) + j(c + d) 

	result.real = real + c2.real;						// 실수부분 덧셈
	result.imag = imag + c2.imag;						// 허수부분 덧셈

	return result;
}


const Cmplx Cmplx::subCmplx(const Cmplx& c2)			// 복소수 뺄셈
{
	Cmplx result;

	// (a + jb) - (c + jd) = (a - b) + j(c - d) 

	result.real = real - c2.real;						// 실수부분 뺼셈
	result.imag = imag - c2.imag;						// 허수부분 뺼셈
		
	return result;
}

const Cmplx Cmplx::mulCmplx(const Cmplx& c2)			// 복소수 곱셈
{
	Cmplx result;

	// (a + jb)(c + jd) = (ac - bd) + j(bc + ad) (이차식 곱셈 이용)

	result.real = (real * c2.real) - (imag * c2.imag);	// 실수부분 곱셈
	result.imag = (real * c2.imag) + (imag * c2.real);	// 허수부분 곱셈

	return result;
}

const Cmplx Cmplx::divCmplx(const Cmplx& c2)
{
	Cmplx result;
	double denom;

	// (a + jb) / (c + jd) = ((ac + bd)/(c² + d²)) + j((bc - ad)/(c² + d²)) (통분 및 이차식 곱셈 이용)

	denom = pow(c2.real, 2) + pow(c2.imag, 2);							// (c² + d²)		

	result.real = ((real * c2.real) + (imag * c2.imag)) / denom;		// 실수부분 나눗셈 방식
	result.imag = ((imag * c2.real) - (real * c2.imag)) / denom;		// 허수부분 나눗셈

	return result;
}



