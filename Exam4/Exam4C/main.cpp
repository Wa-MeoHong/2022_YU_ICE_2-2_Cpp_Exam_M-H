/* �̸� : �Ŵ�ȫ �й� : 21912193
	��¥ : 2022. 12. 16 (��)
	���� : Exam4C_21912193_�Ŵ�ȫ
	���� : Graph�� �̿��Ͽ� ���� ���
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
