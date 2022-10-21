/*
  파일명 : "Exam1B_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- BigArray 클래스를 만들어 출력하는 프로그램
  프로그램 작성자 : 신대홍(2022년 9월 23일)
  최종 Update : Version 1.0.0, 2022년 9월 23일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/09/23		v1.0.0		  최초작성

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "BigArray.h"

using namespace std;

#define ELEMENTS_PER_LINE 10					// 한줄당 출력하는 인수의 개수
#define SAMPLE_LINES 3							// 중간 생략시 출력하는 줄의 개수
#define OUTPUT "output.txt"

int main(void)
{
	ofstream fout;
	fout.open(OUTPUT);								// 파일 열기
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;	exit;
	}

	/*					배열 1					*/
	int big_rand_size = 1000;						// 배열 1은 1000개 생성
	int base_offset = 0;							// 기준점(시작점)은 0부터
	BigArray ba_1(big_rand_size);					// 배열생성

	// 파일에 배열1 생성 후 출력
	fout << "Generating big rand array of " << ba_1.size()
		<< " elements with base_offset (" << base_offset << ") ... " << endl;
	ba_1.genBigRandArray(big_rand_size, base_offset);				// 랜덤 수 생성
	ba_1.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// 파일에 출력
	ba_1.fprintStatistics(fout);								// 랜덤수의 데이터 계산 후 출력
	ba_1.selection_sort();										// 선택정렬
	fout << "Sorted big random array :" << endl;				
	ba_1.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// 선택정렬된 데이터 출력
	cout << "Array 1 print complete!" << endl;

	/*					배열	 2					*/
	big_rand_size = 10000000;									// 1천만개 랜덤수 생성	
	base_offset = -big_rand_size / 2;							// 기준은 -500만
	BigArray ba_2(big_rand_size);								// 배열 2 생성
	
	// 파일에 배열 2생성 후 출력
	fout << endl << "Generating big rand array of " << ba_2.size()
		<< " elements with base_offset (" << base_offset << ") ... " << endl;
	ba_2.genBigRandArray(big_rand_size, base_offset);				// 배열 구하기
	ba_2.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// 배열 출력
	ba_2.fprintStatistics(fout);								// 배열 2 데이터 계산후 출력
	ba_2.quick_sort();											// 퀵정렬 진행
	fout << "Sorted big random array :" << endl;
	ba_2.fprintBigArray(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);	// 퀵정렬된 배열 2 출력
	cout << "Array 2 print complete!" << endl;
	
	fout.close();												// 출력파일 닫기


	return 0;
}