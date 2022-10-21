#include "BigArray.h"
#include <iostream>
#include <iomanip>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)					// 최대값 찾기 매크로함수
#define MIN(x, y) ((x) < (y)) ? (x) : (y)					// 최소값 찾기 매크로함수
#define RANDOMIZE() srand((unsigned int)time(NULL))
#define OFFSET -500000										// offset(기준값)
#define BIG_SIZE 500
#define LINESIZE 10

using namespace std;

int _partition(int* array, int SIZE, int left, int right, int PivotIndex);		// pivot을 기준으로 왼쪽엔 작은값, 오른쪽에 큰값으로 데이터를 옮김
void _quickSort(int* array, int SIZE, int left, int right);						// 퀵정렬 본함수
void suffleArray(int* array, int size);											// 처음 배열 생성할 때, 객체의 멤버함수를 사용못해서 새로 만듦

/*						생성자 및 소멸자						*/
BigArray::BigArray(int n)									// 생성자
{
	array_size = n;											// 먼저 n으로 설정
	memset(&stats, 0, sizeof(Statistics));					// 구조체변수 초기화
}
BigArray::~BigArray()										// 소멸자
{
	cout << "distructed Array" << endl;
	if (big_array != NULL)
		delete[] big_array;
}

/*						배열 생성 관련 함수
		1. 배열 생성 (사이즈와 offset 매개변수로 가짐)
		2. suffleArray( genBigRandArray 전용 )
		3. 클래스 객체가 사용하는 suffle 함수					*/
void BigArray::genBigRandArray(int size, int offset)			// 난수 생성 함수
{
	RANDOMIZE();												// 랜덤 시드 생성

	big_array = new int[size];				// array_size(생성할 랜덤한 수 갯수)만큼 동적할당 

	/*
				>> 중복이 없는 랜덤한 수를 생성하기 때문에 이런 방식도 가능 <<
		1. for문을 통해 0 ~ 생성한 수 까지 1열로 차례대로 배열에 집어넣음
		2. 그 후, suffle을 통해 순서를 섞어버림
	*/
	for (int i = 0; i < size; i++)
	{
		big_array[i] = i + offset;
	}
	suffleArray(big_array, size);
}
void suffleArray(int* array, int size)
{
	int i1, i2, temp, i = 0;

	while (i != size)										// i가 난수 개수까지
	{
		// 바꿀 숫자를 2개 선정함. 선정은 RAND함수로 결정
		i1 = (((unsigned int)rand() << 15) | rand()) % size;
		i2 = (((unsigned int)rand() << 15) | rand()) % size;

		// swapping, 바꿀때는 temp같은 빈 변수 하나가 필요함
		temp = array[i1];
		array[i1] = array[i2];
		array[i2] = temp;

		i++;													// i 증가
	}

}
void BigArray::suffle()								// 섞어주기 (셔플) 함수
{
	int i1, i2, temp, i = 0;

	while (i != array_size)										// i가 난수 개수까지
	{
		// 바꿀 숫자를 2개 선정함. 선정은 RAND함수로 결정
		i1 = (((unsigned int)rand() << 15) | rand()) % array_size;
		i2 = (((unsigned int)rand() << 15) | rand()) % array_size;

		// swapping, 바꿀때는 temp같은 빈 변수 하나가 필요함
		temp = big_array[i1];
		big_array[i1] = big_array[i2];
		big_array[i2] = temp;

		i++;													// i 증가
	}
}

/*						배열 정렬 관련 함수
		1. 선택정렬 (Selection Sort)
		2. 퀵정렬 (Quick Sort)
		3. 퀵정렬 중, Pivot기준으로 작은값, 큰값으로 분류하는 함수
		4. 퀵정렬 본 함수										*/
void BigArray::selection_sort()								// 선택정렬
{
	int min_NUM;											// 작은값 찾기
	int Index_min_NUM;										// 작은값의 인덱스 넘버

	for (int round = 0; round < array_size - 1; round++)
	{
		Index_min_NUM = round;								// 최소값의 인덱스 초기값(round) 설정
		min_NUM = big_array[round];							// 최소값 초기값 설정
		for (int i = round + 1; i < array_size; i++)
		{
			if (big_array[i] < min_NUM)
			{
				Index_min_NUM = i;
				min_NUM = big_array[i];
			}
		}
		if (Index_min_NUM != round)						// 만약 가장 작은 값이 자기자신(기준값)이 아니라면
		{
			big_array[Index_min_NUM] = big_array[round];		// 찾았던 인덱스 주소안의 값을 기준값과 변경
			big_array[round] = min_NUM;						// 가장작은값은 아까 저장했던 그 작은값.
		}
	}

}
void BigArray::quick_sort()
{
	_quickSort(big_array, array_size, 0, array_size - 1);
}
int _partition(int* array, int SIZE, int left, int right, int PivotIndex)
{
	int PivotValue, newPI;
	double temp;

	PivotValue = array[PivotIndex];
	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// 맨 처음 PivotIndex에 있던 값을 맨 오른쪽(혹은 P_I-1위치에 있는 값)과 바꾼다

	newPI = left;						// 이제 새로운 피벗위치를 설정해주는데 초기값은 맨 왼쪽(혹은 P_I + 1위치)으로 설정
	for (int i = left; i <= right - 1; i++)
		// 맨뒤로 가게된 PivotValue는 빼고 나머지 배열들을 범위로 잡는다.
	{
		if (array[i] <= PivotValue)								//만약 맨뒤로 간 PivotValue보다 값이 작다면
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;							// 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
			newPI += 1;
		}
	}
	// 결론적으로 처음 PivotValue값을 기준으로 왼쪽은 PivotValue보다 작은 값들의 배열, 오른쪽은 PivotValue보다 큰 값들의 배열이 형성되었다.
	PivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = PivotValue;

	return newPI;											// newPI 반환
}
void _quickSort(int* array, int SIZE, int left, int right)
{
	int P_I, newPI;

	if (left >= right)					// 만약 left가 right보다 크거나 같다면 newPI반환 중지, 거의 left가 1혹은 0일때이다..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;							// 중간값, 만약 홀수인경우 내림값으로 나누기위치값 산출
	}

	newPI = _partition(array, SIZE, left, right, P_I);


	// 이렇게 왼쪽, 오른쪽 순서대로 작은덩이 → 큰덩이
	if (left < (newPI - 1))									// 이제 newPI기준으로 왼쪽부분
	{
		_quickSort(array, SIZE, left, newPI - 1);
		// 다시 newPI를 산출하면서 크기정렬을 쭉해준다.
	}
	if ((newPI + 1) < right)								// 다음, 왼쪽이 quickSort를 진행후, newPI기준 오른쪽 부분
	{
		_quickSort(array, SIZE, newPI + 1, right);
		// 오른쪽으로 newPI산출및 크기순으로 정렬해준다.
	}
}

/*						배열 데이터 및 출력 관련 함수
		1. 배열 데이터의 연산결과값 산출
		2. 배열 데이터 연산결과 출력 함수
		3. 배열 출력 함수										*/
void BigArray::getStatistics()
{
	double sum = 0; int max = big_array[0], min = big_array[0];		// min, max, sum 변수 생성
	double pow_sum = 0;												// 편차제곱의 합

	for (int i = 0; i < array_size; i++)
	{
		sum += big_array[i];							// 모든 수를 더함
		max = MAX(max, big_array[i]);					// 그 중 최대값 산출
		min = MIN(min, big_array[i]);					// 그 중 최소값 산출
	}
	stats.min = min; stats.max = max;					// stats 구조체에 저장
	stats.avg = sum / array_size;						// stats 구조체에 평균 저장

	
	for (int j = 0; j < array_size; j++)
		pow_sum += pow(big_array[j], 2);				// 제곱의 합을 구함
	stats.var = (pow_sum / array_size) - pow(stats.avg, 2);					// 분산 = 제곱의 평균 - 평균의 제곱
	stats.std_dev = sqrt(stats.var);					// 표준편차 - √분산
}
void BigArray::fprintStatistics(ostream& fout)			// 계산 결과 파일출력
{
	fout.setf(ios::fixed); fout.setf(ios::showpoint); fout.precision(2);
	// fout의 출력 포맷 자리수를 먼저 세팅
	getStatistics();							// 연산결과를 구함
	// 출력
	fout << "Statistics : " << endl;
	fout << " min (" << stats.min << "), max (" << stats.max <<
		"), avg (" << stats.avg << "), var (" << stats.var <<
		"), std_dev (" << stats.std_dev << ")" << endl;
}
void BigArray::fprintBigArray(ostream& fout, int num_per_line, int num_lines)	// 파일 출력 함수
{
	int count = 0;												// 출력할 때 필요함

	int lines = num_lines;
	/*				>>> 출력 방식 <<<
		1. array_size(난수의 개수)에 따라 출력방식을 결정한다.
		2. BIG_SIZE보다 적을 경우, 생략없이 출력
		3. BIG_SIZE보다 많을 경우, 처음 50개 출력하고 나서 중간 생략 후, 끝에 한번더 50개 출력
	*/

	if (array_size < BIG_SIZE)
	{
		lines = array_size / num_per_line;
	}

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < num_per_line; j++)
		{
			if (count == array_size)							// 전부 출력했으면 탈출
				break;
			fout << setw(9) << big_array[count];				// 출력, 자리수를 7로 지정해, 7자리
			count++;
		}
		fout << endl;											// 10개 출력 후 엔터
	}

	// 랜덤한 수가 BIG_SIZE보다 더 큰 경우, 생략 후, 출력한다.
	if (array_size >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// 생략하는 것
		count = array_size - (num_per_line * num_lines);

		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < num_per_line; j++)
			{
				fout << setw(9) << big_array[count];			// 출력
				count++;
			}
			fout << endl;										// 한줄 띄우기
		}
		fout << endl;
	}
}
