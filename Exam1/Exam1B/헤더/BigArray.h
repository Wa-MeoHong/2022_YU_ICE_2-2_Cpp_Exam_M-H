#ifndef BIG_ARRAY_H
#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef struct ArrayStatistics {
	int min;					// 최소값
	int max;					// 최대값
	double avg;					// 평균
	double var;					// 분산
	double std_dev;				// 표준편차
}Statistics;

class BigArray
{
public:
	BigArray(int n);			// constructor (생성자)
	~BigArray();				// destructor (소멸자)
	void genBigRandArray(int size, int offset);		// BigRand 배열을 생성하는 함수
	int size() { return array_size; }				// 배열의 크기 반환
	void suffle();									// 배열 셔플
	void selection_sort();							// 배열 선택정렬
	void quick_sort();								// 배열 퀵정렬
	void getStatistics();							// 배열 데이터 계산
	void fprintStatistics(ostream& fout);			// 배열 데이터 계산결과 출력
	void fprintBigArray(ostream& fout, int num_per_line, int num_lines);		// 배열 파일 출력

private:
	int* big_array = NULL;				// 포인터 변수 big_array
	int array_size = 0;					// 생성할 배열 사이즈
	Statistics stats;			// 배열의 데이터 계산 구조체
};

#endif