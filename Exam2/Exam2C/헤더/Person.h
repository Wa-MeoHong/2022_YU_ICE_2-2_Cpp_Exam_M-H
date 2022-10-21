#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Person
{
public:
	// constructor
	Person() : regID(0), nation(" ") { name = "nobody"; }				// �⺻ ����Ʈ ������
	Person(string n) : regID(0), nation(" ") { name = n; }				// �̸��� ���ڷ� ���� ������

	// getter 
	string Name() const { return name; }				// �̸�
	int RegID() const { return regID; }					// �ֹι�ȣ
	string Nat() const { return nation; }				// ����

	// setter
	void set_Name(string n) { name = n; }		// �̸� ����
	void set_regID(int id) { regID = id; }		// �ֹι�ȣ ����
	void set_Nation(string country) { nation = country; }	// ���� ����


protected:
	string name;						// �̸�
	int regID;							// �ֹι�ȣ
	string nation;						// ����
};

#endif // !PERSON_H
