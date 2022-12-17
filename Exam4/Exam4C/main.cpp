/* 이름 : 신대홍 학번 : 21912193
	날짜 : 2022. 12. 16 (금)
	제목 : Exam4C_21912193_신대홍
	내용 : Graph을 이용하여 도시 출력
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

void main()
{
	Graph graph;

	fgetGraph(&graph, "Korea_11.txt");

	/* Print out Graph based on Adjacency List .. */
	graph.fprintGraph(cout);
	graph.initDistMtrx();
	graph.fprintDistMtrx(cout);

}
