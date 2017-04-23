#include <iostream>
#include <vector>
#include <string>
#include <deque>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::deque;

class AdjVertex;
class Vertex;
class Graph;

int time;//The variable time is a global variable.

void DFS_visit(Graph &G, Vertex *v);

class Vertex
{
public:
	friend class Graph;
	friend void DFS_visit(Graph &G, Vertex *v);

	Vertex() :color("white"), distance(-1), pi(nullptr){}

	void print(Vertex &vNode);

private:
	string color;
	int distance;
	Vertex *pi;
	int position;
	int finish;
};

void Vertex::print(Vertex &vNode)
{
	cout << "position:" << vNode.position << "  color:" << vNode.color << "  distance:" << vNode.distance
		 << "  pi:" << vNode.pi <<  "  finish time:" <<  vNode.finish << endl;
}


class Graph
{
public:
	friend void DFS_visit(Graph &G, Vertex *v);

	Graph() = default;
	Graph(vector<vector<int>> &matrix) :edge(matrix)
	{
		int size = matrix.size();

		for (int i = 0; i != size; ++i)//create a vertex array. 
		{
			Vertex *v = new Vertex;
			v->position = i;
			vert.push_back(v);
		}
	}

	void depth_first_search(Graph &G);

private:
	vector<Vertex*> vert;
	vector<vector<int>> edge;//an adjacency-matrix representation.
};


void Graph::depth_first_search(Graph &G)
{
	time = 0;
	for (int i = 0; i != vert.size(); ++i)
	{
		if (vert[i]->color == "white")
		{
			DFS_visit(G, vert[i]);
		}
	}
}

void DFS_visit(Graph &G, Vertex *v)
{
	time = time + 1;//white vertex v has just been discovered.
	v->distance = time;
	v->color = "gray";
	int pos = v->position;

	for (int i = 0; i != G.vert.size(); ++i)
	{
		if (G.edge[pos][i])//explore edge between v and its adjacency vertices.
		{
			if (G.vert[i]->color == "white")
			{
				G.vert[i]->pi = v;
				DFS_visit(G, G.vert[i]);
			}
		}
	}

	v->color = "black";//blacken v;It is finished. 
	time = time + 1;
	v->finish = time;

	v->print(*v);
}


int main()
{
	//directed graph
	vector<vector<int>> matrix{ { 0, 1, 0, 1, 0, 0 },
								{ 0, 0, 0, 0, 1, 0 },
								{ 0, 0, 0, 0, 1, 1 },
								{ 0, 1, 0, 0, 0, 0 },
								{ 0, 0, 0, 1, 0, 0 },
								{ 0, 0, 0, 0, 0, 1 } };
	Graph G(matrix);

	G.depth_first_search(G);

	system("pause");
	return 0;
}