#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::sort;

#define INT_MAX 100

class Vertex;
class Graph;

class Vertex
{
public:
	friend class Graph;
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend void Dijkstra(Graph &G, const int &s);
	friend int extract_min(vector<Vertex *> &v);
	friend void path_print(Vertex *uNode);
	
	Vertex() :distance(INT_MAX), pi(nullptr){}
	

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
	friend void Dijkstra(Graph &G, const int &s);

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

	Vertex* destination(const int &d)
	{
		return vert[d];
	}

private:
	vector<Vertex*> vert;
	vector<vector<int>> edge;//an adjacency-matrix representation.
};


void Initialize_single_source(Graph &G, const int &s)
{
	G.vert[s]->distance = 0;
}

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


int extract_min(vector<Vertex *> &v)
{
	Vertex* min = v[0];
	int pos = 0;

	for (int i = 1; i != v.size(); ++i)
	{
		if (v[i]->distance < min->distance)
		{
			min = v[i];
			pos = i;
		}
					
	}

	return pos;
}

void path_print(Vertex *uNode)
{
	Vertex* pi = uNode->pi;
	int pi_pos = 0;

	if (pi)
	{
		pi_pos = pi->position;
		cout << pi_pos << "->" << uNode->position << "  distance:" << uNode->distance << endl;

		path_print(pi);
	}
		
}


void Dijkstra(Graph &G, const int &s)
{
	Initialize_single_source(G, s);
	vector<Vertex*> Q = G.vert;
	deque<Vertex*> S;

	while (!Q.empty())
	{
		int pos = extract_min(Q);
		Vertex* uNode = Q[pos];
		auto iter = Q.begin() + pos;
		Q.erase(iter);

		S.push_back(uNode);

		for (int i = 0; i != G.vert.size(); ++i)
		{
			int pos = uNode->position;
			if (G.edge[pos][i])
				Relax(G, uNode, G.vert[i]);
		}
	}
}

int main()
{
	//undirected graph
	vector<vector<int>> matrix{ { 0, 10, 0, 5, 0 },
								{ 0, 0, 1, 2, 0 },
								{ 0, 0, 0, 0, 4 },
								{ 0, 3, 9, 0, 2 },
								{ 7, 0, 6, 0, 0} };
	
	Graph G(matrix);

	Dijkstra(G, 0);

	path_print(G.destination(2));

	system("pause");
	return 0;
}