#include "Dijkstra.h"
#include <time.h>

int main()
{
	vector<vector<int>> matrix;
	//maximum number of vertices we can pass through.
	int vertex_size = 0;
	cout << "Plz enter a maximum number of vertices we could pass£º";
	cin >> vertex_size;
	deque<Vertex*> path;//record the path.

	int start;//beginning.
	int end;//ending.
	vector<int> green_vert;
	//edge that have to be passed through.
	map<int, int> pass_edge;
	//vertices that have to be passed through.
	//edge that mustn't be passed through.
	map<int, int> not_pass_edge;


	/**********************************************************************************
										read file.
	***********************************************************************************/
	ifstream input("../data/case0.txt");
	string s;
	int flag = 0;
	int num;
	int first_vert;
	int secd_vert;
	int row;
	int col;
	int weight;

	if (input)
	{
		while (getline(input, s))
		{
			if (s == "")
				flag += 1;

			istringstream word(s);

			switch (flag)
			{
			case 0://read the start and end.
				word >> start;
				word >> end;
				for (int i = 0; i <= end; ++i)
				{
					vector<int> v(end + 1);
					matrix.push_back(v);
				}
				break;
			case 1://read the green vertices.
				while (word >> num)
					green_vert.push_back(num);
				break;
			case 2://read the not_pass_edge.
				while (word >> first_vert)
				{
					word >> secd_vert;
					not_pass_edge.insert({ first_vert, secd_vert });
				}
				break;
			case 3://read the pass_edge.
				while (word >> first_vert)
				{
					word >> secd_vert;
					pass_edge.insert({ first_vert, secd_vert });
				}
				break;
			case 4://read the adjacency-matrix.
				while (word >> row)
				{
					word >> col;
					word >> weight;
					matrix[row][col] = weight;
					matrix[col][row] = weight;
				}
				break;
			}
		}
	}

	else
		cout << "can't open the file." << endl;

	Graph G1(matrix);//directed graph.
	vector<int> pass_vert = green_vert;
	for (auto &map_it : pass_edge)
	{
		pass_vert.push_back(map_it.first);
		pass_vert.push_back(map_it.second);
	}

	/*************************************************************************
	                       condition 1,2,3,4,5
	**************************************************************************/
	clock_t start_time = clock();
	Conditional_search(G1, start, end, pass_vert, pass_edge, not_pass_edge, path);
	clock_t end_time = clock();


	if (path.size() <= vertex_size)
	{
		int total_cost = path_print(path, G1);
		ofstream output("../result/condition_12345.txt");
		for (auto &elem : path)
			output << output_position(elem) << "->";
		output << "\n";
		output << "number of vertices: " << path.size();
		output << "\n";
		output << "total_cost: " << total_cost << "\n";
		output << "time use: " << double(end_time - start_time) / CLOCKS_PER_SEC;
	}


	else
	{
		cout << "can't find the solution subjecting to constrains of 1,2,3,4,5." << endl;
		cout << endl;
		cout << "other solutions: " << endl;
		int case_choice = 0;
		cout << "which case do you want? " << "\n" << "case1: under condition 1,2,3,4" << endl;
		cout << "case2: under condition 1,2,4,5" << endl;
		cout << "case3: under condition 1,3,4,5" << endl;
		cout << "case4: under condition 1,2,3,5" << endl;
		cout << "Plz enter you choice number: 1 for case1; 2 for case2; 3 for case3; 4 for case4: ";
		cin >> case_choice;

		/*************************************************************************
									condition 1,2,3,4
		**************************************************************************/
		vector<int> pass_vert_copy = pass_vert;
		map<int, int> pass_edge_copy = pass_edge;
		if (case_choice == 1)
		{
			cout << "under condition 1,2,3,4: " << endl;//ignore pass_edge(condition 5).

			Graph G2(matrix);

			auto map_it = pass_edge_copy.begin();

			for (int i = 0; i != pass_edge_copy.size(); ++i)
			{
				int remove = map_it->first;

				for (int j = 0; j < pass_vert_copy.size(); ++j)
				{
					if (pass_vert_copy[j] == remove)
						pass_vert_copy.erase(pass_vert_copy.begin() + j);
				}

				remove = map_it->second;
				for (int j = 0; j < pass_vert_copy.size(); ++j)
				{
					if (pass_vert_copy[j] == remove)
						pass_vert_copy.erase(pass_vert_copy.begin() + j);
				}

				++map_it;
			}

			pass_edge_copy.clear();
			path.clear();

			clock_t start_t = clock();
			Conditional_search(G2, start, end, pass_vert_copy, pass_edge_copy, not_pass_edge, path);
			clock_t end_t = clock();


			if (path.size() <= vertex_size)
			{
				int total_cost = path_print(path, G2);
				ofstream output("../result/condition_1234.txt");
				for (auto &elem : path)
					output << output_position(elem) << "->";
				output << "\n";
				output << "number of vertices: " << path.size();
				output << "\n";
				output << "total_cost: " << total_cost << "\n";
				output << "time use: " << double(end_t - start_t) / CLOCKS_PER_SEC;
			}

			else
				cout << "can't find it";

			cout << endl;
		}


		/*************************************************************************
									condition 1,2,4,5
		**************************************************************************/
		if (case_choice == 2)
		{
			path.clear();
			cout << "under condition 1,2,4,5: " << endl;//ignore condition 3.
			pass_vert_copy.clear();
			pass_vert_copy = pass_vert;
			Graph G3(matrix);

			for (int i = 0; i != green_vert.size(); ++i)
			{
				for (int j = 0; j < pass_vert_copy.size(); ++j)
				{
					if (pass_vert_copy[j] == green_vert[i])
						pass_vert_copy.erase(pass_vert_copy.begin() + j);
				}
			}

			clock_t start_t = clock();
			Conditional_search(G3, start, end, pass_vert_copy, pass_edge, not_pass_edge, path);
			clock_t end_t = clock();


			if (path.size() <= vertex_size)
			{
				int total_cost = path_print(path, G3);
				ofstream output("../result/condition_1245.txt");
				for (auto &elem : path)
					output << output_position(elem) << "->";
				output << "\n";
				output << "number of vertices: " << path.size();
				output << "\n";
				output << "total_cost: " << total_cost << "\n";
				output << "time use: " << double(end_t - start_t) / CLOCKS_PER_SEC;
			}
			else
				cout << "can't find it";

			cout << endl;
		}


		/*************************************************************************
		condition 1,3,4,5
		**************************************************************************/
		if (case_choice == 3)
		{
			path.clear();
			Graph G4(matrix);

			cout << "under condition 1,3,4,5: " << endl;//ignore condition 2.

			clock_t start_t = clock();
			Conditional_search(G4, start, end, pass_vert, pass_edge, not_pass_edge, path);
			clock_t end_t = clock();


			int total_cost = path_print(path, G4);
			ofstream output("../result/condition_1345.txt");
			for (auto &elem : path)
				output << output_position(elem) << "->";
			output << "\n";
			output << "number of vertices: " << path.size();
			output << "\n";
			output << "total_cost: " << total_cost << "\n";
			output << "time use: " << double(end_t - start_t) / CLOCKS_PER_SEC;

			cout << endl;
		}


		/*************************************************************************
		condition 1,2,3,5
		**************************************************************************/
		if (case_choice == 4)
		{
			path.clear();
			Graph G5(matrix);

			cout << "under condition 1,2,3,5(dangerous!): " << endl;//ignore condition 4.
			map<int, int> not_pass_edge_copy = not_pass_edge;
			not_pass_edge_copy.clear();

			clock_t start_t = clock();
			Conditional_search(G5, start, end, pass_vert, pass_edge, not_pass_edge_copy, path);
			clock_t end_t = clock();


			if (path.size() <= vertex_size)
			{
				int total_cost = path_print(path, G5);
				ofstream output("../result/condition_1245.txt");
				for (auto &elem : path)
					output << output_position(elem) << "->";
				output << "\n";
				output << "number of vertices: " << path.size();
				output << "\n";
				output << "total_cost: " << total_cost << "\n";
				output << "time use: " << double(end_t - start_t) / CLOCKS_PER_SEC;
			}
			else
				cout << "can't find it";

			cout << endl;
		}
	}

	system("pause");
	return 0;
}