#include <iostream>
#include <vector>

using namespace std;

#define MY_MAX_INT 9999999999

int neg_cycle(vector<vector<int> >& adj, vector<vector<int> >& cost) 
{
	vector<long long int> distances(adj.size(), MY_MAX_INT);

	distances[0] = 0;

	bool relaxed;
	int v = adj.size();

	for (size_t n = 0; n < v; n++)
	{
		relaxed = false;
		
		for (size_t vi = 0; vi < v; vi++)
		{
			for (size_t neig = 0; neig < adj[vi].size(); neig++)
			{
				long long int dist = distances[vi] + cost[vi][neig];

				if (dist < distances[adj[vi][neig]]) 
				{
					distances[adj[vi][neig]] = dist;
					relaxed = true;
				}
			}
		}
	}
	return relaxed;
}

int main() 
{
	int n, m;
	cin >> n >> m;

	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());

	for (int i = 0; i < m; i++) 
	{
		int x, y, w;
		cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}

	cout << neg_cycle(adj, cost) << endl;

	return 0;
}