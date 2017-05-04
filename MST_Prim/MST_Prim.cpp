#include <iostream>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::multimap;
using std::map;

#define infinite 100;

class Vertex;
class Graph;

void MST_Prim(Graph &G, const int &s);
bool in_Queue_test(vector<Vertex*> Q, Vertex *u);
int Extract_min(vector<Vertex*> Q);


class Vertex
{
public:
	friend class Graph;
	friend void MST_Prim(Graph &G, const int &s);
	friend int Extract_min(vector<Vertex*> Q);

	Vertex() :key(0), pi(nullptr){}

	void print(Vertex &vNode);

private:
	int key;
	Vertex *pi;
	int position;
};


class Graph
{
public:
	friend void MST_Prim(Graph &G, const int &s);

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

void MST_Prim(Graph &G, const int &s)
{
	for (auto &elem : G.vert)
		elem->key = infinite;

	G.vert[s]->key = 0;

	vector<Vertex*> Q;
	for (auto &elem : G.vert)
		Q.push_back(elem);

	while (!Q.empty())
	{
		int min_index = Extract_min(Q);
		Vertex *min_vert = Q[min_index];//Exrtact_min.
		auto iter = Q.begin() + min_index;
		Q.erase(iter);

		if (min_vert->pi)
			cout << min_vert->pi->position << "->" << min_vert->position << endl;

		int pos = min_vert->position;
		for (int i = 0; i != G.vert.size(); ++i)
		{
			if (G.edge[pos][i])
			{
				bool in_Q = in_Queue_test(Q, G.vert[i]);
				if (in_Q && G.edge[pos][i] < G.vert[i]->key)
				{
					G.vert[i]->pi = G.vert[pos];
					G.vert[i]->key = G.edge[pos][i];
				}
			}
		}
	}
}

int Extract_min(vector<Vertex*> Q)
{
	int min_key = Q[0]->key;
	int index = 0;

	for (int i = 1; i != Q.size(); ++i)
	{
		if (min_key > Q[i]->key)
		{
			min_key = Q[i]->key;
			index = i;
		}
	}

	return index;
}
bool in_Queue_test(vector<Vertex*> Q, Vertex *u)
{
	for (auto &elem : Q)
	{
		if (elem == u)
			return true;
	}

	return false;
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
	MST_Prim(G, 0);

	system("pause");
	return 0;
}