/* 이름 : 신대홍 학번 : 21912193
	날짜 : 2022. 12. 16 (금)
	제목 : Exam4D_21912193_신대홍
	내용 : Dijkstra 이용하여 도시 최단거리 루트 찾기
*/


#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_Dijkstra.h"

using namespace std;

void test_DijkstraShortestPathSearch(Graph* pG);

void main()
{
	Graph graph;

	fgetGraph(&graph, "Korea_11.txt");

	graph.fprintGraph(cout);
	graph.initDistMtrx();
	graph.fprintDistMtrx(cout);
	cout << endl;

	test_DijkstraShortestPathSearch(&graph);
}

void test_DijkstraShortestPathSearch(Graph* pG)
{
	VrtxList path;
	BreadthFirstSearch bfsGraph(*pG);

	cout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl;

	path.clear();
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. . to quit) : ";
		cin >> start_nm >> end_nm;
		if (start_nm == ".")
			break;
		pStart = pG->getVertex(start_nm);
		pEnd = pG->getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			return;
		}
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName() << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		printPath(pStart, pEnd, path);

		pEnd = pG->getVertex(start_nm);
		pStart = pG->getVertex(end_nm);
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName() << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		printPath(pStart, pEnd, path);
	}
}
