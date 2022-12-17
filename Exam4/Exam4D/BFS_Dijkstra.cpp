#include "BFS_Dijkstra.h"

void BreadthFirstSearch::initialize()
{ 
}

void BreadthFirstSearch::_bfsTraversal(ostream& fout, Vertex& s, Vertex& target, VrtxList& path)
{
}

void BreadthFirstSearch::setEdgeStatus(Edge& e, EdgeStatus es)
{
}

EdgeStatus BreadthFirstSearch::getEdgeStatus(Edge& e)
{
	return EdgeStatus();
}

void BreadthFirstSearch::DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, VrtxList& path)
{
	double** ppDistMtrx = graph.getppDistMtrx();
	double* pLeastCost, minCost;
	int num_nodes = getNumVertices();
	int num_selected, minID;
	BFSstat* pBFS_STAT;
	int* pPrev;

	Vertex* pVrtxArray = graph.getpVrtxArray();
	Vertex vrtx, v;

	Edge e;
	int  start_vID, target_vID, vID;
	EdgeList* pAdjLstArray = graph.getpAdjLstArray();
	start_vID = s.getID(); target_vID = t.getID();

	pLeastCost = new double[num_nodes];
	pPrev = new int[num_nodes];
	pBFS_STAT = new BFSstat[num_nodes];

	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_STAT[i] = NOT_SELECTed;
	}

	pBFS_STAT[start_vID] = SELECTed;
	num_selected = 1;
	path.clear();

	fout << "Dijkstra:: Least Cost from Vertex (" << s.getName() << ") at each round : " << endl;
	fout << "      |";
	for (int i = 0; i < num_nodes; i++)
		fout << setw(5) << pVrtxArray[i].getName();

	fout << endl;
	fout << "---------+";
	for(int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	}
	fout << endl;

	int round = 0;
	int cost;

	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "]|";
		minID = -1;
		minCost = PLUS_INF;

		for (int i = 0; i < num_nodes; i++)
		{
			if ((pLeastCost[i] < minCost) && pBFS_STAT[i] != SELECTed)
			{
				minID = i;
				minCost = pLeastCost[i];
			}
		}

		// 최소노드를 찾지 못했다면 바로 아웃
		if (minID == -1)
			break;
		else
		{
			pBFS_STAT[minID] = SELECTed;
			num_selected++;
			//만약 그 가장 작은 곳이 목적지라면 바로 탈출
			if (minID == target_vID)
			{
				fout << endl << "reached to the target Node ("
					<< pVrtxArray[minID].getName() << ") at LeastCost = " << minCost << endl;
				vID = minID;

				do
				{
					//최종 목적지에서 다시 역순으로 돌아가 만난 노드를 push
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];
				} while (vID != start_vID);

				// 마지막 처음 노드를 푸쉬후 탈출
				vrtx = pVrtxArray[vID];
				path.push_front(vrtx);
				break;
 			}

		}
		// edge relaxation
		for (int i = 0; i < num_nodes; i++)
		{
			if ((pBFS_STAT[i] != SELECTed) && pLeastCost[i] > pLeastCost[minID] + ppDistMtrx[minID][i])
			{
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
			}
		}

		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << setw(5) << "+oo";
			else
				fout << setw(5) << pLeastCost[i];
		}
		fout << "==> selected vertex : " << pVrtxArray[minID] << endl;

	} //end of while()
}
