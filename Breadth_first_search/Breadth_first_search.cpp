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

class Vertex
{
public:
	Vertex() :color("white"), distance(-1), pi(nullptr){}
	friend class Graph;

	void print(Vertex &vNode);

private:
	string color;
	int distance;
	Vertex *pi;
	int position;
};

void Vertex::print(Vertex &vNode)
{
	cout << "position:" << vNode.position << "  color:" << vNode.color << "  distance:" << vNode.distance
		 <<  "  pi:"<<  vNode.pi << endl;
}


class Graph
{
public:
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

	void Breadth_first_search(Graph &G, const int &s);

private:
	vector<Vertex*> vert;
	vector<vector<int>> edge;//an adjacency-matrix representation.
};


void Graph::Breadth_first_search(Graph &G, const int &s)
{
	vert[s]->color = "gray";
	vert[s]->distance = 0;

	deque<Vertex*> Q;
	Q.push_back(vert[s]);//first-in,first-out deque.

	while (!Q.empty())
	{
		Vertex *vNode = Q.front();
		Q.pop_front();
		int pos = vNode->position;

		for (int i = 0; i != vert.size(); ++i)
		{
			if (edge[pos][i])//find the adjacency vertices of vertex vNode.
			{
				Vertex *adjNode = vert[i];
				if (adjNode->color == "white")
				{
					adjNode->color = "gray";
					adjNode->distance = vNode->distance + 1;
					adjNode->pi = vNode;
					Q.push_back(adjNode);

					(*adjNode).print(*adjNode);
				}
			}
		}

		vNode->color = "black";
	}
}

int main()
{
	vector<vector<int>> matrix{ { 0, 1, 0, 0, 1, 0, 0, 0 },
								{ 1, 0, 0, 0, 0, 1, 0, 0 },
								{ 0, 0, 0, 1, 0, 1, 1, 0 },
								{ 0, 0, 1, 0, 0, 0, 1, 1 },
								{ 1, 0, 0, 0, 0, 0, 0, 0 },
								{ 0, 1, 1, 0, 0, 0, 1, 0 },
								{ 0, 0, 1, 1, 0, 1, 0, 1 },
								{ 0, 0, 0, 1, 0, 0, 1, 0 } };
	Graph G(matrix);

	G.Breadth_first_search(G,1);

	system("pause");
	return 0;
}