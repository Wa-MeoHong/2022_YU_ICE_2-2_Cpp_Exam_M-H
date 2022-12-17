#ifndef INTERCITYDIST_H
#define INTERCITYDIST_H


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class CityPair
{
	friend ostream& operator<<(ostream& ostr, CityPair cp)
	{
		ostr << "(" << cp.city1_name << ", " << cp.city2_name << ")";
		return ostr;
	}
public:
	CityPair() {};
	CityPair(string c1, string c2) :city1_name(c1), city2_name(c2) { 	};
	string getC1() const { return city1_name; }
	string getC2() const { return city2_name; }
	bool operator<(const CityPair other) const {
		if (city1_name < other.city1_name)
			return true;
		else if ((city1_name == other.city1_name) && (city2_name < other.city2_name))
			return true;
		else
			return false;
	}
private:
	string city1_name;
	string city2_name;
};


void fget_ICD(string fname, map<CityPair, double>* pMap_ICD, set<string>& city_names);
void print_set(set<string>& s);
void print_ICD_Map(map<CityPair, double>& map_ICD);
void print_ICD_Table(set<string>& city_names, map<CityPair, double>& map_ICD);


#endif