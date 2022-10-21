#ifndef MTRX_H
#define MTRX_H
#pragma warning(disable: 4996)					// ���� �ȶ߰� �ϴ� pragma����

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Mtrx {
public:
	Mtrx(int num_row, int num_col);					// constructor (������)
	Mtrx(ifstream& fin);
	~Mtrx();										// distructor (�Ҹ���)
	int row() const { return n_row; }
	int col() const { return n_col; }
	void NameSetting(string nm) { name = nm; };
	string Name() const { return name; }
	Mtrx addMtrx(const Mtrx&);						// ��� ����
	Mtrx subMtrx(const Mtrx&);						// ��� ����
	Mtrx mulMtrx(const Mtrx&);						// ��� ����
	void fprintMtrx(ofstream& fout);				// ��� ���� ���

private:
	string name;
	int n_row;
	int n_col;
	double** dMtrx;									// ��� ���� dMtrx
};


#endif // !MTRX_H
