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
deque<Vertex*> Toplogical_sort(Graph &G);
void print_path(deque<Vertex*> &result);

class Vertex
{
public:
	friend class Graph;
	friend void DFS_visit(Graph &G, Vertex *v);
	friend int extract_min(vector<Vertex *> &v);
	friend void print_path(deque<Vertex*> &result);

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
		<< "  pi:" << vNode.pi << "  finish time:" << vNode.finish << endl;
}

class Graph
{
public:
	friend void DFS_visit(Graph &G, Vertex *v);
	friend deque<Vertex*> Toplogical_sort(Graph &G);

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

	//v->print(*v);
}

int extract_min(vector<Vertex *> &v)
{
	Vertex* min = v[0];
	int pos = 0;

	for (int i = 1; i != v.size(); ++i)
	{
		if (v[i]->finish < min->finish)
		{
			min = v[i];
			pos = i;//index
		}

	}

	return pos;
}

//Toplogically sorts a dag(directed acyclic graph).
deque<Vertex*> Toplogical_sort(Graph &G)
{
	G.depth_first_search(G);
	deque<Vertex*> result;
	vector<Vertex*> v_vert = G.vert;

	while (!v_vert.empty())
	{
		int pos = extract_min(v_vert); 
		auto iter = v_vert.begin() + pos;
		Vertex* min_vert = v_vert[pos];
		v_vert.erase(iter);

		result.push_front(min_vert);
	}

	return result;
}

void print_path(deque<Vertex*> &result)
{
	for (auto iter : result)
	{
		cout << "position:" << iter->position << " discover time:" << iter->distance
			<< " finish time:" << iter->finish << " ->" << endl;
	}
}

int main()
{
	//directed graph
	vector<vector<int>> matrix{ { 0, 1, 0, 0, 0, 0, 0, 1, 0},
								{ 0, 0, 1, 0, 0, 0, 0, 1, 0 },
								{ 0, 0, 0, 0, 0, 1, 0, 0, 0 },
								{ 0, 0, 1, 0, 1, 0, 0, 0, 0 },
								{ 0, 0, 0, 0, 0, 1, 0, 0, 0 },
								{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
								{ 0, 0, 0, 0, 0, 0, 0, 1, 0 }, 
								{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
								{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
	Graph G(matrix);

	deque<Vertex*> result = Toplogical_sort(G);

	print_path(result);

	system("pause");
	return 0;
}