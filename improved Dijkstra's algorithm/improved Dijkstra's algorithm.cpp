#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;
using std::map;

#define INT_MAX 100

class Vertex;
class Graph;

void Initialize_single_source(Graph &G, const int &s);
void Relax(Graph &G, Vertex *u, Vertex *v);
void Dijkstra(Graph &G, const int &s);
void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
	                    map<int, int> &pass_edge, map<int, int> &not_pass_edge);
int extract_min(vector<Vertex *> &v);
void path_print(Vertex *uNode, const int &s);
int detect_min(vector<Vertex *> &v);

class Vertex
{
public:
	friend class Graph;
	friend void Initialize_single_source(Graph &G, const int &s);
	friend void Relax(Graph &G, Vertex *u, Vertex *v);
	friend void Dijkstra(Graph &G, const int &s);
	friend int extract_min(vector<Vertex *> &v);
	friend void path_print(Vertex *uNode, const int &s);
	friend void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
		                           map<int, int> &pass_edge, map<int, int> &not_pass_edge);
	friend int detect_min(vector<Vertex *> &v);
	
	Vertex() :distance(INT_MAX), pi(nullptr),color("white"){}
	

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
		                           map<int, int> &pass_edge, map<int, int> &not_pass_edge);
	friend int detect_min(vector<Vertex *> &v);

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
	for (int i = 0; i != G.vert.size(); ++i)
	{
		G.vert[i]->distance = INT_MAX;
		G.vert[i]->pi = nullptr;
	}
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

void path_print(Vertex *uNode, const int &s)
{
	Vertex* pi = uNode->pi;
	int pi_pos = 0; 

	if (pi)
	{
		if (uNode->position != s)
		{
			pi_pos = pi->position;
			cout << pi_pos << "->" << uNode->position << "  distance:" << uNode->distance << endl;
			path_print(pi, s);
		}
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

/*int detect_min(vector<Vertex *> &v)
{
	int min = 0;

}*/

void Conditional_search(Graph &G, const int &st, const int &ed, vector<int> &pass_vert,
	                    map<int, int> &pass_edge, map<int, int> &not_pass_edge)
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


	while(!vert_set.empty())
	{
		Dijkstra(G, star->position);

		int vert_pos = extract_min(vert_set);
		Vertex* pass = vert_set[vert_pos];//a vertex we must pass through.
		auto it = vert_set.begin() + vert_pos;
		vert_set.erase(it);

		int pos = pass->position;//index of vector<Vertex*> vert;

		//detect the vertex is close to the edge that must be passed through or not. 
		auto iter = pass_edge.begin();

		Dijkstra(G, star->position);
		path_print(G.destination(pos), star->position);
		star = pass;

		while (iter != pass_edge.end())
		{
			if (iter->first == pos && G.vert[pos]->color == "white")
			{
				G.vert[pos]->color = "gray";
				G.vert[iter->second]->color = "gray";

				int dis = G.vert[pos]->distance + G.edge[pos][iter->second];

				cout << pos << " -> " << iter->second << " distance:" << dis << endl;

				for (int i = 0; i < vert_set.size(); ++i)//jump across the vertex passed through.
				{
					if (vert_set[i]->position == iter->second)
						vert_set.erase(vert_set.begin() + i);
				}
				
				star = G.vert[iter->second];
			}

			if (iter->second == pos && G.vert[pos]->color == "white")
			{
				G.vert[pos]->color = "gray";
				G.vert[iter->first]->color = "gray";

				int dis = G.vert[pos]->distance + G.edge[pos][iter->first];

				cout << pos << " -> " << iter->first << " distance:" << dis << endl;

				for (int i = 0; i < vert_set.size(); ++i)//jump across the vertex passed through.
				{
					if (vert_set[i]->position == iter->first)
						vert_set.erase(vert_set.begin() + i);
				}

				star = G.vert[iter->first];
			}

			++iter;
		}
	}

	Dijkstra(G, star->position);
	path_print(G.destination(ed), star->position);
}

int main()
{
	//undirected graph.
	vector<vector<int>> matrix = {
		{ 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//s
		{ 3, 0, 1, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0 },//1
		{ 1, 1, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//2
		{ 1, 0, 1, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//3
		{ 0, 1, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },//4
		{ 0, 0, 1, 2, 1, 0, 1, 0, 0, 3, 1, 0, 3, 0, 0, 0, 0, 0 },//5
		{ 0, 0, 0, 2, 0, 1, 0, 1, 2, 0, 0, 0, 2, 4, 3, 0, 0, 0 },//6
		{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//7
		{ 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0 },//8
		{ 0, 4, 0, 0, 1, 3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },//9
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 0, 0, 0, 0, 0 },//10
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0 },//11
		{ 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 2, 1, 0, 2, 0, 0, 1, 0 },//12
		{ 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2, 0, 1, 2, 2, 1 },//13
		{ 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0 },//14
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 1, 0, 0, 4 },//15
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 1 },//16
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 1, 0 },//E
	};
	
	Graph G(matrix);

	int start = 0;
	int end = 17;
	//vertices that have to be passed through.
	vector<int> pass_vert{ 2, 4, 7, 12, 13, 14};
	//edge that have to be passed through.
	map<int ,int> pass_edge{ { 2, 4 }, { 13, 14 } };
	//edge that mustn't be pass through.
	map<int, int> not_pass_edge{ { 11, 12 } };

	Conditional_search(G, start, end, pass_vert, pass_edge, not_pass_edge);

	system("pause");
	return 0;
}