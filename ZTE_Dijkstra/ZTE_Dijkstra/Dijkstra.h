#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ofstream;
using std::istringstream;
using std::vector;
using std::string;
using std::map;
using std::deque;

#define infinite 100

class Vertex;
class Graph;

//initialize each vertex's distance and pi value.(for Dijkstra)
void Initialize_single_source(Graph &G, const int &s);
//relax edges.(for Dijkstra)
void Relax(Graph &G, Vertex *u, Vertex *v);
//maintain a set of vertices whose final shortest-path weights from 
//the source s have been determined.
void Dijkstra(Graph &G, const int &s);
//conditional search .
void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
	map<int, int> &pass_edge, map<int, int> &not_pass_edge, deque<Vertex*> &path);
//extract a vertex with minimum distance.
int extract_min(vector<Vertex *> &v);
//print the path.
int path_print(deque<Vertex *> &v, Graph &G);
/**************************************************************************************
             quicksort for vertices' distance in increasing order.
**************************************************************************************/
int partion(vector<Vertex*> &v, const int &p, const int &r);
void quicksort(vector<Vertex*> &v, const int &p, const int &r);
vector<Vertex*> vert_sort(vector<Vertex*> vert);
int output_position(Vertex*);//output the position of a vertex.


class Vertex
{
public:
	friend class Graph;
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend void Dijkstra(Graph &G, const int &s);
	friend int extract_min(vector<Vertex *> &v);
	friend int path_print(deque<Vertex *> &v, Graph &G);
	friend void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
		map<int, int> &pass_edge, map<int, int> &not_pass_edge, deque<Vertex*> &path);
	friend int partion(vector<Vertex*> &v, const int &p, const int &r);
	friend void quicksort(vector<Vertex*> &v, const int &p, const int &r);
	friend int output_position(Vertex*);

	Vertex() :distance(infinite), pi(nullptr), color("white"){}//vertex initialization.


private:
	int distance;
	Vertex *pi;
	int position;
	string color;
};

class Graph
{
public:
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend void Dijkstra(Graph &G, const int &s);
	friend void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
		map<int, int> &pass_edge, map<int, int> &not_pass_edge, deque<Vertex*> &path);
	friend int path_print(deque<Vertex *> &v, Graph &G);

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

/***************************************************************
function:
   quicksort for vertices' distance in increasing order.
*****************************************************************/
int partion(vector<Vertex*> &v, const int &p, const int &r)
{
	Vertex *x = v[r];
	int i = p - 1;

	for (int j = p; j != r; ++j)
	{
		if (v[j]->distance < x->distance)
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


/****************************************************************
function:
   extract a vertex with minimum distance.
input:
   v:a vector contains vertices.
output:
   a vertex position.It has a minimum distance.
*****************************************************************/
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

/****************************************************************
function:
   print path.
input:
   v: a deque contains recorded vertices along the path.
   G: a Graph.
output:
   total cost.
*****************************************************************/
int path_print(deque<Vertex *> &v, Graph &G)
{
	Vertex* next = nullptr;
	int total = 0;

	int row = 0;//edge's loacation.
	int col = 0;

	for (int i = 0; i != v.size() - 1; ++i)
	{
		cout << v[i]->position << " -> ";
		next = v[i + 1];

		row = v[i]->position;
		col = next->position;
		total += G.edge[row][col];
	}

	cout << v.back()->position;
	cout << endl;
	cout << "total cost:" << total << endl;

	return total;
}

/*********************************************************************
function:
   maintain a set of vertices whose final shortest-path weights from
the source s have been determined.
input:
  G; a Graph.
  s: source position.
output:
  void.
**********************************************************************/
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

/***************************************************************************************
function:
   conditional search.
input:
   G: a Graph.
   st: source position.
   ed: destination position.
   pass_vert: vertices to be passed through.
   pass_edge: edges to be passed through.
   not_pass_edge: no pass edges.
   path: path.
output:
   void.
****************************************************************************************/

void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
	map<int, int> &pass_edge, map<int, int> &not_pass_edge, deque<Vertex*> &path)
{
	Vertex* star = G.vert[st];
	int row = 0;
	int col = 0;

	auto map_it = not_pass_edge.begin();
	while (map_it != not_pass_edge.end())
	{
		row = map_it->first;
		col = map_it->second;

		G.edge[row][col] = 0;//make the weight be zero,since we can't pass through it.
		G.edge[col][row] = 0;

		++map_it;
	}

	vector<Vertex*> vert_set;
	for (int i = 0; i != pass_vert.size(); ++i)
		vert_set.push_back(G.vert[pass_vert[i]]);


	path.push_back(star);//reacord the head.
	//detect the vertex is close to the edge that must be passed through or not. 

	while (!vert_set.empty())
	{
		auto iter = pass_edge.begin();
		while (iter != pass_edge.end())
		{
			if (iter->first == star->position && star->color == "white")
			{
				star->color = "gray";
				G.vert[iter->second]->color = "gray";

				//record the path.
				path.push_back(G.vert[iter->second]);

				for (int i = 0; i < vert_set.size(); ++i)//jump across the vertex passed through.
				{
					if (vert_set[i]->position == iter->second)
						vert_set.erase(vert_set.begin() + i);
				}

				star = G.vert[iter->second];
			}

			if (iter->second == star->position && star->color == "white")
			{
				star->color = "gray";
				G.vert[iter->first]->color = "gray";

				//record the path.
				path.push_back(G.vert[iter->first]);


				for (int i = 0; i < vert_set.size(); ++i)//jump across the vertex passed through.
				{
					if (vert_set[i]->position == iter->first)
						vert_set.erase(vert_set.begin() + i);
				}

				star = G.vert[iter->first];
			}

			++iter;
		}

		Dijkstra(G, star->position);
		int vert_pos = 0;
		int branch_num = 0;
		vector<Vertex*> Q_sort;
		Vertex *pass;

		if (!vert_set.empty())
		{
			Q_sort = vert_sort(vert_set);

			for (int i = 1; i != Q_sort.size(); ++i)//detect how many minium vertices there are. 
			{
				if (Q_sort[i]->distance == Q_sort[0]->distance)
					branch_num = i;
			}

			if (branch_num == 0)
				vert_pos = 0;//the first one in the Q_sort is minimum.
			else
			{
				path_print(path, G);
				cout << "branches are following: " << endl;

				vector<int> cost_v;

				for (int i = 0; i != branch_num + 1; ++i)
				{
					deque<Vertex*> branch;
					int total_cost = 0;
					Vertex *branch_star = Q_sort[i];

					int next_st = branch_star->position;
					vector<int> pass_vert_copy;

					for (int i = 0; i != vert_set.size(); ++i)
					{
						if (vert_set[i]->position != next_st)
							pass_vert_copy.push_back(vert_set[i]->position);
					}

					Conditional_search(G, next_st, ed, pass_vert_copy, pass_edge, not_pass_edge, branch);
					total_cost = path_print(branch, G);

					cost_v.push_back(total_cost);

					auto iter_edge = pass_edge.begin();
					while (iter_edge != pass_edge.end())
					{
						for (int i = 0; i != vert_set.size(); ++i)//turn vertices into white.
						{
							if (vert_set[i]->position == iter_edge->first ||
								vert_set[i]->position == iter_edge->second)
								vert_set[i]->color = "white";
						}
						++iter_edge;
					}
				}

				int min = cost_v[0];
				int dermin = 0;
				for (int i = 1; i != cost_v.size(); ++i)
				{
					if (min > cost_v[i])
						dermin = i;
				}
				vert_pos = dermin;
			}

			pass = Q_sort[vert_pos];//a vertex we must pass through.
			for (int i = 0; i < vert_set.size(); ++i)
			{
				if (vert_set[i]->position == pass->position)
					vert_set.erase(vert_set.begin() + i);
			}

			Dijkstra(G, star->position);

			Vertex *temp = pass;
			deque<Vertex*> Q_temp;
			while (temp && temp->position != star->position)//record the path.
			{
				Q_temp.push_back(temp);
				temp = temp->pi;
			}
			while (!Q_temp.empty())
			{
				Vertex* temp_vert = Q_temp.back();
				path.push_back(temp_vert);
				Q_temp.pop_back();
			}

			star = pass;
		}
	}

	Dijkstra(G, star->position);
	Vertex *end_vert = G.vert[ed];

	Vertex *temp = end_vert;
	deque<Vertex*> Q_temp;
	while (temp && temp->position != star->position)//record the path.
	{
		Q_temp.push_back(temp);
		temp = temp->pi;
	}
	while (!Q_temp.empty())
	{
		Vertex* temp_vert = Q_temp.back();
		path.push_back(temp_vert);
		Q_temp.pop_back();
	}

}

int output_position(Vertex *vert)
{
	return vert->position;
}
