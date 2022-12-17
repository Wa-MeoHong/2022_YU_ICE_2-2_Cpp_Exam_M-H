/* �̸� : �Ŵ�ȫ �й� : 21912193
	��¥ : 2022. 12. 16 (��)
	���� : Exam4A_21912193_�Ŵ�ȫ
	���� : STL set, map�� �̿��Ͽ� ���� ���
*/

#include <iostream>
#include <map>
#include <set>
#include "InterCityDist.h"
using namespace std;

int main()
{
	map<CityPair, double> map_KR_icd;
	set<string> major_KR_cities;

	cout << "2022-2 ��ü�������α׷��ְ� �ڷᱸ�� �й�:21912193 �̸�: �Ŵ�ȫ" << endl;
	fget_ICD("Korea_11.txt", &map_KR_icd, major_KR_cities);

	cout << "Korean Major Cities = ";
	print_set(major_KR_cities);
	print_ICD_Map(map_KR_icd);
	print_ICD_Table(major_KR_cities, map_KR_icd);

	return 0;
}



