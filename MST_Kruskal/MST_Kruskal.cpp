#include <iostream>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::multimap;
using std::map;
using std::set;

class Vertex;
class Graph;

void Make_set(Vertex*);
void Union(Vertex*, Vertex*);
void Link(Vertex*, Vertex*);
Vertex* Find_set(Vertex*);
multimap<int,int> MST_Kruskal(Graph &G);


class Vertex
{
public:
	friend class Graph;
	friend void Make_set(Vertex*);
	friend void Union(Vertex*, Vertex*);
	friend void Link(Vertex*, Vertex*);
	friend Vertex* Find_set(Vertex*);
	friend multimap<int,int> MST_Kruskal(Graph &G);

	Vertex() :rank(0), pi(nullptr){}

	void print(Vertex &vNode);

private:
	int rank;
	Vertex *pi;
	int position;
};

void Vertex::print(Vertex &vNode)
{
	cout << "position:" << vNode.position << "  distance:" << vNode.rank
		<< "  pi:" << vNode.pi << endl;
}


class Graph
{
public:
	friend multimap<int, int> MST_Kruskal(Graph &G);

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

private:
	vector<Vertex*> vert;
	vector<vector<int>> edge;//an adjacency-matrix representation.
};

void Make_set(Vertex *u)
{
	u->pi = u;
	u->rank = 0;
}

void Union(Vertex *u, Vertex *v)
{
	Link(Find_set(u), Find_set(v));
}

void Link(Vertex *u, Vertex *v)
{
	if (u->rank > v->rank)
		v->pi = u;
	else
	{
		u->pi = v;
		if (u->rank == v->rank)
			v->rank = v->rank + 1;
	}
}

Vertex* Find_set(Vertex *u)
{
	if (u != u->pi)
		u->pi = Find_set(u->pi);
	return u->pi;
}


multimap<int, int> MST_Kruskal(Graph &G)
{
	multimap<int, int> A;

	for (auto &elem : G.vert)
		Make_set(elem);

	multimap<int, map<int, int>> sorted_edge;//trick:ordered container.
	for (int i = 0; i != G.edge.size(); ++i)
	for (int j = 0; j != G.edge.size(); ++j)
	{
		if (i <= j && G.edge[i][j])
		{
			map<int, int> edge_pair{ { i, j } };
			sorted_edge.insert({G.edge[i][j], edge_pair});
		}       
	}
	
	for (auto &elem : sorted_edge)
	{
		map<int, int> edge_pair{ elem.second };
		for (auto &it : edge_pair)
		{
			Vertex *u(G.vert[it.first]);
			Vertex *v(G.vert[it.second]);
			if (Find_set(u) != Find_set(v))
			{
				A.insert({ u->position, v->position });
				Union(u, v);
			}
		}
	}

	return A;
}

int main()
{
	vector<vector<int>> matrix{ { 0, 4, 0, 0, 0, 0, 8, 0, 0 },
								{ 4, 0, 8, 0, 0, 0, 11, 0, 0 },
								{ 0, 8, 0, 7, 2, 0, 0, 0, 4 },
								{ 0, 0, 7, 0, 0, 9, 0, 0, 14 },
								{ 0, 0, 2, 0, 0, 0, 7, 6, 0 },
								{ 0, 0, 0, 9, 0, 0, 0, 0, 10 },
								{ 8, 11, 0, 0, 7, 0, 0, 1, 0 },
								{ 0, 0, 0, 0, 6, 0, 1, 0, 2 },
								{ 0, 0, 4, 14, 0, 10, 0, 2, 0 } };
	Graph G(matrix);
	multimap<int, int> result = MST_Kruskal(G);

	for (auto &elem : result)
	{
		cout << elem.first << " " << elem.second << endl;
	}

	system("pause");
	return 0;
}