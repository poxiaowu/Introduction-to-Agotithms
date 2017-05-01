#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

#define infinite 100

class Vertex;
class Graph;


//initialize each vertex's distance and pi value.
void Initialize_single_source(Graph &G, const int &s);
//relax edges.
void Relax(Graph &G, Vertex *u, Vertex *v);
bool Bellman_Ford(Graph &G, const int &s);
void path_print(Graph &G);


class Vertex
{
public:
	friend class Graph;
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend bool Bellman_Ford(Graph &G, const int &s);
	friend void path_print(Graph &G);
	
	Vertex() :distance(infinite), pi(nullptr){}//vertex initialization.


private:
	int distance;
	Vertex *pi;
	int position;
};


class Graph
{
public:
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend bool Bellman_Ford(Graph &G, const int &s);
	friend void path_print(Graph &G);

	Graph() = default;
	Graph(vector<vector<int>> &matrix) :edge(matrix)//Graph initialization.
	{
		int size = matrix.size();

		for (int i = 0; i != size; ++i)//create a vertex array. 
		{
			Vertex *v = new Vertex;
			v->position = i;
			vert.push_back(v);
		}
	}

	Vertex* destination(const int &d)
	{
		return vert[d];
	}

private:
	vector<Vertex*> vert;//contain all the vertices.
	vector<vector<int>> edge;//an adjacency-matrix representation.
};

/******************************************************************
function:
   initialize each vertex's distance and pi value.(for Dijkstra)
input:
   G: a Graph
   s: source position.
output:
   void.
*******************************************************************/
void Initialize_single_source(Graph &G, const int &s)
{
	for (int i = 0; i != G.vert.size(); ++i)
	{
		G.vert[i]->distance = infinite;
		G.vert[i]->pi = nullptr;
	}
	G.vert[s]->distance = 0;
}

/******************************************************************
function£º
   relax edges.(for Dijkstra)
input:
   G:a Graph.
   u:a vertex.
   v:a vertex.
output:
   void.
********************************************************************/
void Relax(Graph &G, Vertex *u, Vertex *v)
{
	int i = u->position;
	int j = v->position;
	int w = G.edge[i][j];

	if (v->distance > u->distance + w)
	{
		v->distance = u->distance + w;
		v->pi = u;
	}
}

bool Bellman_Ford(Graph &G, const int &s)
{
	Initialize_single_source(G, s);

	for (int i = 0; i != G.vert.size()- 1; ++i)//make |V|-1 passes.
	{
		for (int j = 0; j != G.vert.size(); ++j)
		for (int k = 0; k != G.vert.size(); ++k)
		{
			if (G.edge[j][k])
				Relax(G, G.vert[j], G.vert[k]);//relax all |E| edges.
		}
	}

	for (int i = 0; i != G.vert.size(); ++i)
	for (int j = 0; j != G.vert.size(); ++j)
	{
		if (G.edge[i][j])
		{
			if (G.vert[j]->distance > G.vert[i]->distance + G.edge[i][j])
				return false;
		}
	}

	return true;
}

void path_print(Graph &G)
{
	for (auto elem : G.vert)
		cout << elem->position << " " << "distance:" << elem->distance << endl;
}

int main()
{
	vector<vector<int>> matrix = 
	{
		{0,6,0,7,0},
		{0,0,5,8,-4},
		{0,-2,0,0,0},
		{0,0,-3,0,9},
		{2,0,7,0,0}
	};

	Graph G(matrix);

    bool result = Bellman_Ford(G, 0);

	if (result)
		path_print(G);

	system("pause");
	return 0;
}