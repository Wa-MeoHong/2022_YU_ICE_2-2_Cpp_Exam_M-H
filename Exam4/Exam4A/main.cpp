/* 이름 : 신대홍 학번 : 21912193
	날짜 : 2022. 12. 16 (금)
	제목 : Exam4A_21912193_신대홍
	내용 : STL set, map을 이용하여 도시 출력
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

	cout << "2022-2 객체지향프로그래밍과 자료구조 학번:21912193 이름: 신대홍" << endl;
	fget_ICD("Korea_11.txt", &map_KR_icd, major_KR_cities);

	cout << "Korean Major Cities = ";
	print_set(major_KR_cities);
	print_ICD_Map(map_KR_icd);
	print_ICD_Table(major_KR_cities, map_KR_icd);

	return 0;
}



