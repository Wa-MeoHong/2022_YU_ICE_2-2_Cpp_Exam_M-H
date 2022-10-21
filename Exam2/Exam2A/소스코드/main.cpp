/*
  파일명 : "Exam2A_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Class Mtrx, Class MtrxArray를 구성하여, 연산자 오버로딩을 통해 행렬의 연산결과를 출력하는 알고리즘
	- 행렬, 실수 연산은 단순히 모든 요소에 실수를 사칙연산함
	- 행렬, 행렬 연산은 기존의 행렬연산을 사용함

  프로그램 작성자 : 신대홍(2022년 10월 21일)
  최종 Update : Version 1.0.0, 2022년 10월 21일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/10/21		v1.0.0		  최초작성
===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Class_Mtrx.h"
#include "Class_MtrxArray.h"

#define INPUT "Matrix_data.txt"
#define OUTPUT "output.txt"
#define NUM_MTRX 10

int main(void)
{
	ifstream fin;
	ofstream fout;

	fin.open(INPUT);		// Matrix_data.txt 오픈
	if (fin.fail())
	{
		// 파일을 열지 못하면 오류가 남
		cout << "Error in opening Matrix_data.txt !!";
		exit(-1);
	}

	fout.open(OUTPUT);		// Matrix_data.txt 오픈
	if (fout.fail())
	{
		// 파일을 열지 못하면 오류가 남
		cout << "Error in opening output.txt !!";
		exit(-1);
	}

	// MtrxArray 생성
	MtrxArray mtrx(NUM_MTRX);

	// 파일 입력 (차례대로 들어감), 그후 이름설정
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	mtrx[0].NameSetting("mtrx[0]");
	mtrx[1].NameSetting("mtrx[1]");
	mtrx[2].NameSetting("mtrx[2]");

	// 콘솔출력, 파일출력
	cout << mtrx[0]; fout << mtrx[0];
	cout << mtrx[1]; fout << mtrx[1];
	cout << mtrx[2]; fout << mtrx[2];

	// 행렬에 정수연산 ( 덧셈, 뺄셈, 곱셈)
	
	// 행렬[0] + 2.0 ( 각요소에 전부 더함)
	mtrx[3] = mtrx[0] + 2.0;
	mtrx[3].NameSetting("mtrx[3] = mtrx[0] + 2.0");
	cout << mtrx[3]; fout << mtrx[3];			// 출력

	// 행렬[0] - 2.0 ( 각요소에 전부 뻄)
	mtrx[4] = mtrx[0] - 2.0;					
	mtrx[4].NameSetting("mtrx[4] = mtrx[0] - 2.0");
	cout << mtrx[4]; fout << mtrx[4];			// 출력

	// 행렬[0] * 2.0 ( 각요소에 전부 곱함)
	mtrx[5] = mtrx[0] * 2.0;
	mtrx[5].NameSetting("mtrx[5] = mtrx[0] * 2.0");
	cout << mtrx[5]; fout << mtrx[5];			// 출력

	// 행렬[0] + 행렬[1] (행렬덧셈)
	mtrx[6] = mtrx[0] + mtrx[1];
	mtrx[6].NameSetting("mtrx[6] = mtrx[0] + mtrx[1]");
	cout << mtrx[6]; fout << mtrx[6];			// 출력

	// 행렬[0] - 행렬[1] (행렬뺄셈)
	mtrx[7] = mtrx[0] - mtrx[1];
	mtrx[7].NameSetting("mtrx[7] = mtrx[0] - mtrx[1]");
	cout << mtrx[7]; fout << mtrx[7];			// 출력

	// 행렬[0] - 행렬[2] (행렬곱셈)
	mtrx[8] = mtrx[0] * mtrx[2];
	mtrx[8].NameSetting("mtrx[3] = mtrx[0] * mtrx[2]");
	cout << mtrx[8]; fout << mtrx[8];			// 출력

	// ~행렬[0] (전치행렬)
	mtrx[9] = ~mtrx[0];
	mtrx[9].NameSetting("mtrx[9] = transposed(mtrx[0])");
	cout << mtrx[9]; fout << mtrx[9];			// 출력



	return 0;
}