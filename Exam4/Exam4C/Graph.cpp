#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void fgetGraph(Graph* g, string fin_name)
{
	//Graph* graph;

	string gName, city1, city2;
	int num_nodes; 
	double dist;

	ifstream fin(fin_name);
	if (fin.fail())
	{
		cout << "Error!";
		exit(-1);
	}
	
	fin >> gName >> num_nodes;
	cout << "initializing graph " << gName << "from input data file (" << fin_name <<")" << endl;
	g->initGraph(gName, num_nodes);

	while (!fin.eof())
	{
		fin >> city1 >> city2 >> dist;

		Vertex vrtx1(city1, 0), vrtx2(city2, 0);
		g->insertVertex (vrtx1); g->insertVertex(vrtx2);
		// 간선이 반대로도 가므로 2번 넣는다.
		vrtx1 = *(g->getVertex(city1));  vrtx2 = *(g->getVertex(city2));
		Edge edges(vrtx1, vrtx2, dist);
		cout << "insert" << edges << endl;
		g->insertEdge(edges);
		Edge edge2(vrtx2, vrtx1, dist);
		g->insertEdge(edge2);
	}
	cout << endl;
}
