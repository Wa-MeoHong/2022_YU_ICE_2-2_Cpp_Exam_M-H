#include "Class_MtrxArray.h"
#include "CLass_Mtrx.h"

/*					생성자, 소멸자				
		1. MtrxArray (생성자)
		2. ~MtrxArray (소멸자)					*/
MtrxArray::MtrxArray(int array_size)						// 행렬 배열 초기 설정 
{
	mtrxArraySIZE = array_size;								// 배열의 크기 
	pMtrx = new Mtrx[array_size];							// 동적할당
}
MtrxArray::~MtrxArray()										// 배열 소멸자
{
	if (pMtrx != NULL)
	{
		delete[] pMtrx;										// 배열 동적할당 해제
	}
}

/*					member funcitions
		1. subError() ( 만약 인덱스번호가 오류나면 출력하는 함수)
		2. ArraySize() ( 배열의 크기 반환)					
		3. isValidIndex(index) ( 인덱스가 유효한지 유효성검사 )
		4. operator[](sub) ( 배열의 인덱스에 있는 값 반환 )*/
void subError()												// 에러 출력 함수
{
	cout << "ERROR: Subscript out of range.\n";	exit(0);
}

Mtrx& MtrxArray::operator[](int sub)						// 배열 인덱스로 불러오는 연산자 [] 오버로드
{
	if (isValidIndex(sub))									// 배열 인덱스 번호가 유효한지 확인
		return pMtrx[sub];									// 유효하면 배열의 인덱스에 해당되는 데이터 반환
	else
		subError();											// 아니면 에러 메세지 후 종료
}

int MtrxArray::ArraySize()									// 배열의 크기 반환
{
	return mtrxArraySIZE;
}

bool MtrxArray::isValidIndex(int index)						// 배열 인덱스 유효성 검사
{
	if (index < 0 || index >= this->ArraySize())				// 배열인덱스 번호가 0부터 SIZE-1사이에 있는 숫자인지
		return false;										// 아니면 false, 맞으면 true
	else
		return true;
}