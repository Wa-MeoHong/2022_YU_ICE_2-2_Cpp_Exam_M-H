/** Exam4D - BFS_Dijkstra.h */

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "Graph.h"
#include <fstream>

using namespace std;
typedef enum BFS_PROCESS_STATUS { NOT_SELECTed, SELECTed } BFSstat ;

class BreadthFirstSearch
{
protected:
	typedef Graph::Vertex Vertex;
	typedef Graph::Edge Edge;
	typedef std::list<Vertex> VrtxList;
	typedef std::list<Edge> EdgeList;
protected:
	Graph& graph;
	bool done;	// flag of search done

protected:
	void initialize();
	void _bfsTraversal(ostream& fout, Vertex& s, Vertex& target, VrtxList& path);
	virtual bool isDone() const { return done; }
	void setEdgeStatus(Edge& e, EdgeStatus es);
	EdgeStatus getEdgeStatus(Edge& e);
	bool isValidVrtxID(int vid) { return graph.isValidvID(vid); }
	int getNumVertices() { return graph.getNumVertices(); }
	Graph& getGraph() { return graph; }
public:
	BreadthFirstSearch(Graph& g) :graph(g), done(false) {
		g.initDistMtrx();

	}
	void DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, VrtxList& path);
};
#endif