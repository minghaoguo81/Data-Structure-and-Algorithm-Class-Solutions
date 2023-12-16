#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MY_MAX_INT 999999

int dist(vector<vector<int> >& adj, int s, int t) 
{
	vector<int> distances(adj.size(), -1);
	queue<int> my_queue;
	distances[s] = 0;
	my_queue.push(s);

	while (!my_queue.empty())
	{
		int actual_vertix = my_queue.front();
		my_queue.pop();

		if (actual_vertix == t)
			return distances[actual_vertix];

		for (size_t i = 0; i < adj[actual_vertix].size(); i++)
		{
			if (distances[adj[actual_vertix][i]] == -1)
			{
				distances[adj[actual_vertix][i]] = distances[actual_vertix] + 1;
				my_queue.push(adj[actual_vertix][i]);
			}
		}
	}

	return distances[t];
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

	int s, t;
	cin >> s >> t;
	s--, t--;
	cout << dist(adj, s, t) << endl;

	return 0;
}