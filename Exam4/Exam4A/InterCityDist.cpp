#include "InterCityDist.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

void fget_ICD(string fname, map<CityPair, double>* pMap_ICD, set<string>& city_names)
{
	// 파일열기
	ifstream fin(fname);
	if (fin.fail())
	{
		cout << "Error in opening file " << fname << " !! ";
		exit(-1);
	}

	// 도시 이름, 시티의 개수 
	string city1, city2, setName;
	int num_city = 0, dist;

	// 이름과 도시 개수 가져옴
	fin >> setName >> num_city;

	// 파일을 다 읽을때까지 도시1, 도시2, 거리를 읽고
	// makepair해서 map에 넣어줌
	while (!fin.eof())
	{
		fin >> city1 >> city2 >> dist;
		CityPair cityPairs(city1, city2), cityPairs2(city2, city1);
		city_names.insert(city1);	city_names.insert(city2);
		pMap_ICD->insert(make_pair(cityPairs, dist));
		pMap_ICD->insert(make_pair(cityPairs2, dist));

	}
	fin.close();
}

void print_set(set<string>& s)
{
	set<string>::iterator sItor;

	cout << "Korean Major Cities = [";
	sItor = s.begin();
	while (sItor != s.end())
	{
		cout << *sItor << ", ";
		sItor++;
	}
	cout << "]" << endl << endl;
}

void print_ICD_Map(map<CityPair, double>& map_ICD)
{
	map<CityPair, double>::iterator mItor;

	cout << "InterCityDistance Map = " << endl;
	mItor = map_ICD.begin();

	while (mItor != map_ICD.end())
	{
		CityPair cp;
		double distance;

		cp = (*mItor).first;
		distance = (*mItor).second;
		cout << cp << " : ";
		printf("%.2lf \n", distance); 

		mItor++;
	}
	cout << endl; 
}

void print_ICD_Table(set<string>& city_names, map<CityPair, double>& map_ICD)
{
	set<string>::iterator sItor, s1, s2;
	map<CityPair, double>::iterator mItor;
	string city1, city2;
	double dist;
	// 테이블 출력
	cout << "InterCityDistance Table = " <<endl;
	cout << "\t|";
	sItor = city_names.begin();
	while (sItor != city_names.end())
	{
		cout << setw(7) << *sItor;
		sItor++;
	}
	cout << endl;

	cout << "--------+";
	sItor = city_names.begin();
	while (sItor != city_names.end())
	{
		cout << "-------";
		sItor++;
	}
	cout << endl;

	s1 = city_names.begin();
	while (s1 != city_names.end())
	{
		cout << setw(7) << *s1 << " |";
		s2 = city_names.begin();
		while (s2 != city_names.end())
		{
			if (*s1 == *s2)		// 자기자신이라면 0을 출력 후, s2++하고 다시 시작
			{
				printf("%7.2lf", 0.0);
				s2++;
				continue;
			}
			CityPair findcp(*s1, *s2);

			mItor = (map_ICD.find(findcp));		// 키값을 통해 찾아서 주소를 가져옴

			if (mItor == map_ICD.end())						// 주소값이 없다면 무한대
				cout << setw(7) << "+oo";
			else
			{
				dist = (*mItor).second;
				printf("%7.2lf", dist);	// 아니면 값을 출력 
			}
			s2++;
		}
		cout << endl;
		s1++;
	}
	
}

