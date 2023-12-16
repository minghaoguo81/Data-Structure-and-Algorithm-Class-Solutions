#include <iostream>
#include <vector>

using namespace std;

#define NOT_EXPLORED 0
#define BEING_EXPLORED 1
#define FULLY_EXPLORED 2

int explore(vector<vector<int> >& adj, vector<int>& state, int x)
{
	state[x] = BEING_EXPLORED;
	bool IsCycle = false;
	size_t i = 0;
	while ((i < adj[x].size()) && (IsCycle == false))
	{
		if (state[adj[x][i]] == NOT_EXPLORED)
			IsCycle = explore(adj, state, adj[x][i]);
		else if (state[adj[x][i]] == BEING_EXPLORED)
		{
			IsCycle = true;
		}
		i++;
	}
	state[x] = FULLY_EXPLORED;
	return IsCycle;
}

int acyclicity(vector<vector<int> >& adj, int n_vertices, int n_edges)
{
	if (n_vertices == 0 || n_edges == 0)
		return 0;

	bool IsCycle = false;
	size_t i = 0;
	vector<int> state(n_vertices, NOT_EXPLORED);

	while ((i < n_vertices) && (IsCycle == false))
	{
		IsCycle = explore(adj, state, i);
		i++;
	}
	return IsCycle;
}

int main() 
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());

	for (size_t i = 0; i < m; i++) 
	{
		int x, y;
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}

	cout << acyclicity(adj, n, m) << endl;

	return 0;
}