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

void DFS_visit(Graph &G, Vertex *v, bool &flag);
vector<vector<int>> matrix_transpose(vector<vector<int>> &matrix);
vector<Vertex*> vert_sort(vector<Vertex*> vert);

class Vertex
{
public:
	friend class Graph;
	friend void DFS_visit(Graph &G, Vertex *v, bool &flag);
	friend vector<Vertex*> vert_sort(vector<Vertex*> vert);
	friend int partion(vector<Vertex*> &v, const int &p, const int &r);
	friend void quicksort(vector<Vertex*> &v, const int &p, const int &r);

	Vertex() :color("white"), distance(-1), pi(nullptr){}

private:
	string color;
	int distance;
	Vertex *pi;
	int position;
	int finish;
};



class Graph
{
public:
	friend void DFS_visit(Graph &G, Vertex *v, bool &flag);

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

	void depth_first_search(Graph &G, bool &flag);
	void strongly_connected_components(Graph &G);

private:
	vector<Vertex*> vert;
	vector<vector<int>> edge;//an adjacency-matrix representation.
};

//quicksort which sorts into increasing order.
int partion(vector<Vertex*> &v, const int &p, const int &r)
{
	Vertex *x = v[r];
	int i = p - 1;

	for (int j = p; j != r; ++j)
	{
		if (v[j]->finish < x->finish)
		{
			i = i + 1;
			Vertex* temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}
	}

	Vertex* temp = v[i + 1];
	v[i + 1] = v[r];
	v[r] = temp;

	return i + 1;
}

void quicksort(vector<Vertex*> &v, const int &p, const int &r)
{
	if (p < r)
	{
		int q = partion(v, p, r);
		quicksort(v, p, q - 1);
		quicksort(v, q + 1, r);
	}
}


vector<Vertex*> vert_sort(vector<Vertex*> vert)
{
	quicksort(vert, 0, vert.size() - 1);

	return vert;
}


void Graph::depth_first_search(Graph &G, bool &flag)
{
	time = 0;
	vector<vector<int>> transe_edge = matrix_transpose(G.edge);
	Graph trans_G(transe_edge);
	vector<Vertex*> new_vert = vert_sort(G.vert);

	for (int i = 0; i != vert.size(); ++i)
	{
		if (flag)//second time to call DFS
		{
			int pos = 0;
			Vertex *max_vert = new_vert.back();
			pos = max_vert->position;
			new_vert.pop_back();

			if (trans_G.vert[pos]->color == "white")
			{
				cout << "strongly connected components: " << trans_G.vert[pos]->position << " ";
				DFS_visit(trans_G, trans_G.vert[pos], flag);
				cout << endl;
			}
				
		}
		else
		{
			if (vert[i]->color == "white")
			{
				DFS_visit(G, vert[i], flag);
			}
		}
	}
}

void DFS_visit(Graph &G, Vertex *v, bool &flag)
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
				if (flag)
					cout << G.vert[i]->position << " ";
				DFS_visit(G, G.vert[i], flag);
			}
		}
	}

	v->color = "black";//blacken v;It is finished. 
	time = time + 1;
	v->finish = time;
}


vector<vector<int>> matrix_transpose(vector<vector<int>> &matrix)
{
	vector<vector<int>> transpose = matrix;
	int col_size = matrix[0].size();
	 
	for (int i = 0; i != matrix.size(); ++i)
	for (int j = 0; j != col_size; ++j)
		transpose[j][i] = matrix[i][j];
	
	return transpose;
}

void Graph::strongly_connected_components(Graph &G)
{
	bool flag = 0;//true, if it is the second time to call DFS.

	G.depth_first_search(G, flag);

	flag = 1;
	G.depth_first_search(G, flag);
}


int main()
{
	//directed graph
	vector<vector<int>> matrix{ { 0, 1, 0, 0, 0, 0, 0, 0 },
								{ 0, 0, 1, 0, 1, 1, 0, 0 },
								{ 0, 0, 0, 1, 0, 0, 1, 0 },
								{ 0, 0, 1, 0, 0, 0, 0, 1 },
								{ 1, 0, 0, 0, 0, 1, 0, 0 },
								{ 0, 0, 0, 0, 0, 0, 1, 0 },
								{ 0, 0, 0, 0, 0, 1, 0, 1 },
								{ 0, 0, 0, 0, 0, 0, 0, 1 } };
	Graph G(matrix);

	G.strongly_connected_components(G);

	system("pause");
	return 0;
}