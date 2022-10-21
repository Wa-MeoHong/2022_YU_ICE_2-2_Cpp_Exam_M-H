#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#pragma warning(disable: 4996)					// ���� �ȶ߰� �ϴ� pragma����

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class MtrxArray;

class Mtrx {
	friend ostream& operator<< (ostream&, const Mtrx&);
	friend istream& operator>> (istream&, Mtrx&);
	friend class MtrxArray;

public:
	Mtrx();											// constructor (������)
	Mtrx(string nm, int n_row, int n_col);
	Mtrx(string nm, double* pA, int n_row, int n_col);
	~Mtrx();										// distructor (�Ҹ���)
	void init(int num_row, int num_col);
	void NameSetting(string nm) { name = nm; };
	string Name() const { return name; }
	int row() const { return n_row; }
	int col() const { return n_col; }
	const Mtrx operator+(const Mtrx&);				// ��� ����
	const Mtrx operator+(double a);					// ������ ����
	const Mtrx operator-(const Mtrx&);				// ��� ����
	const Mtrx operator-(double a);					// ������ ����
	const Mtrx operator*(const Mtrx&);				// ��� ����
	const Mtrx operator*(double a);					// ������ ����
	const Mtrx operator~();							// ��ġ ��� 

	const Mtrx& operator=(const Mtrx&);
	bool operator==(const Mtrx&);					// ����� ������ Ȯ��
	bool operator!=(const Mtrx&);					// ����� �ٸ��� Ȯ��

private:
	string name;
	int n_row;
	int n_col;
	double** dMtrx = NULL;									// ��� ���� dMtrx
};


#endif // !CLASS_MTRX_H