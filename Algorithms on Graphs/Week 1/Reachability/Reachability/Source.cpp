#include <iostream>
#include <vector>

using namespace std;

void explore(vector<vector<int> >& adj, vector<int>& group, int actual_group, int x)
{
	group[x] = actual_group;
	for (size_t i = 0; i < adj[x].size(); i++)
	{
		if (group[adj[x][i]] == 0)
			explore(adj, group, actual_group, adj[x][i]);
	}
}

int reachability(vector<vector<int> >& adj, int x, int y)
{
	int n_vertices = adj.size();
	vector<int> group(n_vertices, 0);

	int actual_group = 1;

	explore(adj, group, actual_group, x);
	actual_group++;

	return (group[x] == group[y]);
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
		adj[y - 1].push_back(x - 1);
	}

	int x, y;
	cin >> x >> y;
	cout << reachability(adj, x - 1, y - 1) << endl;

	return 0;
}