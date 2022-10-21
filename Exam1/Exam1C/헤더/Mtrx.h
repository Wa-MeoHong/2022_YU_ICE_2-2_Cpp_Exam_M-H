#ifndef MTRX_H
#define MTRX_H
#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Mtrx {
public:
	Mtrx(int num_row, int num_col);					// constructor (생성자)
	Mtrx(ifstream& fin);
	~Mtrx();										// distructor (소멸자)
	int row() const { return n_row; }
	int col() const { return n_col; }
	void NameSetting(string nm) { name = nm; };
	string Name() const { return name; }
	Mtrx addMtrx(const Mtrx&);						// 행렬 덧셈
	Mtrx subMtrx(const Mtrx&);						// 행렬 뺄셈
	Mtrx mulMtrx(const Mtrx&);						// 행렬 곱셈
	void fprintMtrx(ofstream& fout);				// 행렬 파일 출력

private:
	string name;
	int n_row;
	int n_col;
	double** dMtrx;									// 행렬 변수 dMtrx
};


#endif // !MTRX_H
