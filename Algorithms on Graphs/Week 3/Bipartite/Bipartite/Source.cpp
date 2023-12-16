#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bipart(vector<vector<int> >& adj) 
{
	vector<bool> team(adj.size(), false);
	vector<bool> visited(adj.size(), false);
	queue<int> my_queue;

	team[0] = 0;
	my_queue.push(0);

	while (!my_queue.empty())
	{
		int actual_vertex = my_queue.front();
		my_queue.pop();
		visited[actual_vertex] = true;

		for (size_t i = 0; i < adj[actual_vertex].size(); i++)
		{
			if (!visited[adj[actual_vertex][i]])
			{
				team[adj[actual_vertex][i]] = !team[actual_vertex];
				my_queue.push(adj[actual_vertex][i]);
			}
			else
			{
				if (team[adj[actual_vertex][i]] == team[actual_vertex])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int main() 
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());

	for (int i = 0; i < m; i++) 
	{
		int x, y;
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}

	cout << bipart(adj) << endl;

	return 0;
}