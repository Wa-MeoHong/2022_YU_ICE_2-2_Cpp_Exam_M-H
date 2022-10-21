#include "Mtrx.h"

/*				constructor (생성자)
	1. 열(num_row), 행(num_col)을 알고있는 상태에서 만드는 행렬( 데이터는 0.0으로 초기화 )
	2. 열과 행, 데이터를 모두 파일에서 받아와서 만드는 행렬
															*/
Mtrx::Mtrx(int num_row, int num_col)
{
	n_row = num_row;						// 열 대입
	n_col = num_col;						// 행 대입
	dMtrx = new double* [n_row];				// new 연산자를 통해 double* 형의 배열 생성 ( 원소개수가 n_row개 만큼 )
	for (int i = 0; i < n_row; i++)			// new 연산자를 통해 double 형의 배열 생성 ( 배열당 n_col개 만큼)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// 값을 대입함 ( 0.0으로 )
	{
		for (int k = 0; k < n_col; k++)
		{
			dMtrx[j][k] = 0.0;
		}
	}

}
Mtrx::Mtrx(ifstream& fin)
{
	fin >> n_row >> n_col;					// 열과 행의 데이터를 파일에서 읽어옴

	dMtrx = new double* [n_row];			// new 연산자를 통해 double* 형의 배열 생성 ( 원소개수가 n_row개 만큼 )
	for (int i = 0; i < n_row; i++)			// new 연산자를 통해 double 형의 배열 생성 ( 배열당 n_col개 만큼)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// 파일로부터 데이터를 읽어옴
	{
		for (int k = 0; k < n_col; k++)
		{
			if (fin.eof())
				dMtrx[j][k] = 0.0;			// 만약 파일에서 데이터를 모두 읽었으나 초기값 설정이 안끝났다면 0.0으로 
			else {
				fin >> dMtrx[j][k];			// 파일애서 데이터를 읽어와 배열에 저장
			}
		}
	}
}

/*				 distructor (소멸자)					*/
Mtrx::~Mtrx()
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete 연산자를 통해 동적할당한 배열을 해제
	//}
	//delete[] dMtrx;							// 또한번 delete를 통한 동적할당 해제
}

/*				 행렬 연산 관련 멤버
	1. 행렬 덧셈 ( 다른 배열 하나를 const 변수로 들고와 계산)
	2. 행렬 뺄셈 ( 다른 배열 하나를 const 변수로 들고와 계산)
	3. 행렬 곱셈 ( 다른 배열 하나를 const 변수로 들고와 계산)
	5. 행렬 내의 최대, 최소값 계산
												*/
Mtrx Mtrx::addMtrx(const Mtrx& mM)								// 행렬 덧셈
{
	Mtrx mR(n_row, n_col);										// 결과 행렬 생성
	mR.NameSetting("Add Mtrx");									// 이름 지정

	for (int i = 0; i < n_row; i++)								// 행렬 덧셈 진행
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;													// 행렬 반환
}
Mtrx Mtrx::subMtrx(const Mtrx& mM)								// 행렬 뺄셈
{
	Mtrx mR(n_row, n_col);										// 결과 행렬 생성
	mR.NameSetting("Sub Mtrx");

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] - mM.dMtrx[i][j];
	}

	return mR;
}
Mtrx Mtrx::mulMtrx(const Mtrx& mM)							// 행렬 곱셈 함수
{
	int row_SIZE, col_SIZE, SIZE_k;

	row_SIZE = n_row; col_SIZE = mM.col(); SIZE_k = mM.row();	// 결과를 담는 행렬의 행, 열데이터 
	Mtrx mR(row_SIZE, col_SIZE);							// 행, 열 데이터를 가지고 행렬 생성
	mR.NameSetting("Mul Mtrx");								// 이름 설정

	for (int i = 0; i < row_SIZE; i++)						// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)					// 열 전환
		{
			for (int k = 0; k < SIZE_k; k++)				// 인수를 곱한것들 덧셈하기
			{
				mR.dMtrx[i][j] += dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}

/*					행렬 출력 함수					*/
void Mtrx::fprintMtrx(ofstream& fout)						// 파일 출력함수
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )

	fout << name << " = " << endl;
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{

			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				fout << a6 << a3;										// ┌
			else if (i > 0 && i < n_row - 1 && k == 0)
				fout << a6 << a2;										// │
			else if (i == n_row - 1 && k == 0)
				fout << a6 << a6;										// └

			fout.setf(ios::fixed);  fout.setf(ios::showpoint);
			fout << setw(7); fout.precision(2);
			fout << dMtrx[i][k];						// 숫자 출력부분


			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == n_col - 1)
				fout << a6 << a4;										// ┐
			else if (i > 0 && i < n_row - 1 && k == n_col - 1)
				fout << a6 << a2;										// │
			else if (i == n_row - 1 && k == n_col - 1)
				fout << a6 << a5;										// ┘
		}
		fout << endl;
	}
	fout << endl;

}
