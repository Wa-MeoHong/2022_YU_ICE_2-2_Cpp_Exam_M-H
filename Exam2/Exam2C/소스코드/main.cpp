/*
  ���ϸ� : "Exam2C_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- �Լ� ���ø��� �����Ͽ� �л� �����͸� �����
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 21��)
  ���� Update : Version 1.0.0, 2022�� 10�� 21��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/21		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include <iostream>
#include "Student.h"
#include "T_Array.h"

#define OUTPUT "output.txt"
#define NUM_STUDENTS 10

int main(void)
{

	// �л� ������
	Student students[NUM_STUDENTS] =
	{
		Student(5555, "Kim", 10205, "Korea", 3.57),
		Student(1234, "Lee", 11213, "Korea", 4.37),
		Student(4444, "Park", 12227, "Korea", 3.72),
		Student(2222, "Hao", 10121, "China", 2.35),
		Student(3333, "James", 11219, "USA", 3.89),
		Student(6666, "Thomas", 12320, "UK", 4.42),
		Student(7777, "Leon", 10722, "France", 4.12),
		Student(9999, "Carlo", 11519, "Italy", 4.35),
		Student(1000, "Tanaka", 13920, "Japan", 3.21),
		Student(8888, "Wang", 10622, "China", 3.45)
	};

	// �л� ������ ����
	T_Array<Student*, int> stArray_keySTID(NUM_STUDENTS, "T_Array<Student, keyST_ID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keySTID.insert(i, &students[i]);
	}
	// �ʱ� ���
	cout << "T_Array<Student_keyID> at Initialization :" << endl;
	stArray_keySTID.print(1);

	// �л� �����͸� ST_ID(�й�)���� �������� (��������)
	stArray_keySTID.selection_sort(string("ST_ID"), INCREASING);
	cout << "T_Array<Student_keyID> after selection sorting (increase order) :" << endl;
	stArray_keySTID.print(1);


	// �л� ������ ����
	T_Array<Student*, string> stArray_keyName(NUM_STUDENTS, "T_Array<Student, keyST_ID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyName.insert(i, &students[i]);
	}
	// �л� �����͸� NAME(�̸�)���� �������� (��������)
	stArray_keyName.selection_sort(string("NAME"), INCREASING);
	cout << "T_Array<Student_keyName> after selection_sorting (increasing order) by Name :" << endl;
	stArray_keyName.print(1);


	// �л� ������ ����
	T_Array<Student*, double> stArray_keyGPA(NUM_STUDENTS, "T_Array<Student, keyGPA>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyGPA.insert(i, &students[i]);
	}
	// �л� �����͸� GPA(����)���� �������� (��������)
	stArray_keyGPA.selection_sort(string("GPA"), DECREASING);
	cout << "T_Array<Student_keyGPA> after selection_sorting (decreasing order) by GPA:" << endl;
	stArray_keyGPA.print(1);

	// �л� ������ ����
	T_Array<Student*, int> stArray_keyRegID(NUM_STUDENTS, "T_Array<Student, keyRegID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyRegID.insert(i, &students[i]);
	}
	// �л� �����͸� REG_ID(�ֹε��)���� �������� (��������)
	stArray_keyRegID.merge_sort(string("REGID"), INCREASING);
	cout << "Student_keyRegID after merge_sorting (increasing order) by regID :" << endl;
	stArray_keyRegID.print(1);

	// �л� ������ ����
	T_Array<Student*, string> stArray_keyNation(NUM_STUDENTS, "T_Array<Student, keyNation>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyNation.insert(i, &students[i]);
	}
	// �л� �����͸� NATION(����)���� �������� (��������)
	stArray_keyNation.merge_sort(string("NATION"), INCREASING);
	cout << "Student_keyNation after merge sorting (increasing order) by nation : " << endl;
	stArray_keyNation.print(1);

	return 0;
}