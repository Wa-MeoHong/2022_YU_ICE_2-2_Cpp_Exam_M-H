/** Graph.h */
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

#define PLUS_INF INT_MAX/2 
enum VrtxStatus { UN_VISITED, NOT_SELECTED, VISITED, SELECTED, VRTX_SELECTED, VRTX_NOT_SELECTED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_NOT_SELECTED, EDGE_VISITED, EDGE_SELECTED, EDGE_NOT_FOUND };

class Graph  // Graph based on Adjacency Matrix
{
public:
	class Vertex;
	class Edge;
	typedef std::list<Graph::Vertex> VrtxList;
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Graph::Vertex>::iterator VrtxItor;
	typedef std::list<Graph::Edge>::iterator EdgeItor;
public:
	class Vertex  // Graph::Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex v)
		{
			fout << "Vertex(" << v.getName() << ")";
			return fout;
		}
	public:
		Vertex() : name(), ID(-1) {}
		Vertex(string n, int id) : name(n), ID(id) { }
		Vertex(int id) : ID(id) {}
		string getName() { return name; }
		void setName(string c_name) { name = c_name; }
		int getID() { return ID; }
		void setID(int id) { ID = id; }
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; }
		VrtxStatus getvrtxStatus() { return vrtxStatus; }
		bool operator==(Vertex other) { return ((ID == other.getID()) && (name == other.getName())); }
		bool operator!=(Vertex other) { return ((ID != other.getID()) || (name != other.getName())); }
	private:
		string name;
		int ID;
		VrtxStatus vrtxStatus;
	};  // end class Vertex

public:
	class Edge  // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e)
		{
			// 출력문 
			fout << "Edge(" << setw(2) << (*e.getpVrtx_1()).getName() << "-> " << setw(2) << (*e.getpVrtx_2()).getName();
			fout << ": " << setw(2) << e.distance << ") ";

			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {}
		Edge(Vertex& v1, Vertex& v2, double d)
			:distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED)
		{ }

		void endVertices(VrtxList& vrtxLst)
		{
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		Vertex opposite(Vertex v)
		{
			if (v == *pVrtx_1)
				return *pVrtx_2;
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			else {
				//cout << "Error in opposite()" << endl;
				return Vertex(NULL);
			}
		}
		Vertex* getpVrtx_1() { return pVrtx_1; }
		Vertex* getpVrtx_2() { return pVrtx_2; }
		double getDistance() { return distance; }
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; }
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; }
		void setDistance(int d) { distance = d; }
		bool operator!=(Edge e) {
			// 간선이 완전히 똑같지 않으면 일치x
			return ((getpVrtx_1() != e.pVrtx_1) || (pVrtx_2 != e.pVrtx_2));
		}
		bool operator==(Edge e) {
			// 간선이 완전히 똑같으면 일치
			return ((getpVrtx_1() == e.pVrtx_1) && (pVrtx_2 == e.pVrtx_2));
			}
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; }
		EdgeStatus getEdgeStatus() { return edgeStatus; }
	private:
		Vertex* pVrtx_1;
		Vertex* pVrtx_2;
		double distance;
		EdgeStatus edgeStatus;
			}; // end class Edge


public:
	Graph() : name(""), pVrtxArray(NULL), pAdjLstArray(NULL), num_vertices(0) {}  // default constructor
	Graph(string nm, int num_nodes) : name(nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		//num_vertices = num_nodes;
		initGraph(nm, num_nodes);
	}
	string getName() { return name; }
	void initGraph(string nm, int num_nodes)
	{
		name = nm;
		pVrtxArray = new Vertex[num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			pVrtxArray[i] = NULL;
 		}

		pAdjLstArray = new EdgeList[num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			pAdjLstArray[i].clear();
		}

		ppDistMtrx = new double* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			ppDistMtrx[i] = new double[num_nodes];
		}
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				ppDistMtrx[i][j] = PLUS_INF;
			}
		}
		num_vertices = 0;
	}
	void vertices(VrtxList & vrtxLst)
	{
		vrtxLst.clear();
		for (int i = 0; i < getNumVertices(); i++)
		{
			vrtxLst.push_back(pVrtxArray[i]); // 정점 리스트 담기
		}
	}
	void edges(EdgeList & edges)
	{
		EdgeItor eItor;
		Graph::Edge e;

		edges.clear();

		for (int i = 0; i < getNumVertices(); i++)
		{
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				edges.push_back(*eItor);
				eItor++;
			}
		}
	}
	Vertex* insertVertex(Vertex & newV)
	{
		int vID;
		string vName;
		vName = newV.getName();

		for (int i = 0; i < num_vertices; i++)
		{
			if (pVrtxArray[i].getName() == vName)
				return &pVrtxArray[i];
		}

		// 만약 없으면
		vID = getNumVertices();
		newV.setID(vID);
		if (pVrtxArray[vID] == NULL)
		{
			pVrtxArray[vID] = newV;
			this->num_vertices++;
		}
		return &pVrtxArray[vID];
	}
	Vertex* getVertex(string vName)
	{
		for (int i = 0; i < getNumVertices(); i++)
		{
			if (pVrtxArray[i].getName() == vName)
				return &pVrtxArray[i];
		}
		return NULL;
	}
	void insertEdge(Edge & e)
	{
		// 간선을 삽입
		Vertex vrtx_1, vrtx_2;
		int vrtx_1_ID, vrtx_2_ID;

		vrtx_1 = *e.getpVrtx_1(); vrtx_2 = *e.getpVrtx_2();
		vrtx_1_ID = vrtx_1.getID(); vrtx_2_ID = vrtx_2.getID();

		if (pVrtxArray[vrtx_1_ID] == NULL)
			pVrtxArray[vrtx_1_ID] = vrtx_1;
		if (pVrtxArray[vrtx_2_ID] == NULL)
			pVrtxArray[vrtx_2_ID] = vrtx_2;

		e.setpVrtx_1(&pVrtxArray[vrtx_1_ID]);
		e.setpVrtx_2(&pVrtxArray[vrtx_2_ID]);

		pAdjLstArray[vrtx_1_ID].push_back(e);
	}
	int getNumVertices() { return num_vertices; }
	void incidentEdges(Vertex v, EdgeList & edgeLst)
	{
		Graph::Edge e;

		EdgeItor eItor;
		int vID = v.getID();
		// 이 노드와 연결된 간선만 받음
		eItor = pAdjLstArray[vID].begin();
		while (eItor != pAdjLstArray[vID].end())
		{
			edgeLst.push_back(*eItor);
			eItor++;
		}
	}
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }
	double** getppDistMtrx() { return ppDistMtrx; }
	void initDistMtrx() {
		int curVID, vID;

		for (int i = 0; i < num_vertices; i++)
		{
			curVID = pVrtxArray[i].getID();
			EdgeItor pe = pAdjLstArray[curVID].begin();
			while (pe != pAdjLstArray[curVID].end())			// 각 노드의 간선들 전부 삽입
			{
				vID = (*(*pe).getpVrtx_2()).getID();
				ppDistMtrx[curVID][vID] = (*pe).getDistance();		// 거리 삽입		
				pe++;
			}
			ppDistMtrx[curVID][curVID] = 0.0;		// 자기자신은 0
		}
	}
	void fprintDistMtrx(ostream & fout) {
		double dist;

		fout << "\nDistance Matrix of Graph ( " << this->getName() << "): " << endl;
		fout << "     |";
		for (int i = 0; i < num_vertices; i++)
		{
			fout << setw(5) << pVrtxArray[i].getName();
		}
		fout << endl;

		fout << "-------+";
		for (int i = 0; i < num_vertices; i++)
			fout << "-----";
		fout << endl;

		//하나의 정점에 관한 다른 모든 정점간 거리 출력
		for (int i = 0; i < num_vertices; i++)
		{
			fout << setw(7) << pVrtxArray[i].getName() << " |";
			for (int j = 0; j < num_vertices; j++)
			{
				dist = ppDistMtrx[i][j];
				if (dist == PLUS_INF)
					fout << setw(5) << "+oo";		// 무한대 기호
				else
					fout << setw(5) << dist;		// 거리
			}
			fout << endl;

		}
	}
	void fprintGraph(ostream & fout)
	{
		EdgeItor eItor;
		Graph::Edge e;
		int numOutgoingEdges;

		fout << getName() << " with " << this->getNumVertices() << " vertices has following adjacency lists : " << endl;
		for (int i = 0; i < num_vertices; i++)
		{
			fout << pVrtxArray[i] << ": ";
			numOutgoingEdges = pAdjLstArray[i].size();
			eItor = pAdjLstArray[i].begin();

			while (eItor != pAdjLstArray[i].end())
			{
				fout << *eItor << " ";
				eItor++;
			}
			fout << endl;
		}
	}
	bool isValidvID(int vid)
	{
		//만약 인덱싱 번호가 유효하면(안에있으면) true 아니면 false
		if (vid >= 0 && vid < num_vertices)
			return true;
		return false;
	}
private:
	string name;
	Vertex* pVrtxArray; // dynamically created array
	EdgeList* pAdjLstArray; // dynamically created array
	int num_vertices;
	double** ppDistMtrx;
};

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef Graph::VrtxList VrtxList;
typedef Graph::EdgeList EdgeList;
typedef Graph::VrtxItor VrtxItor;
typedef Graph::EdgeItor EdgeItor;

void fgetGraph(Graph* g, string fin_name);
void printPath(Vertex* pStart, Vertex* pEnd, VrtxList path);

#endif