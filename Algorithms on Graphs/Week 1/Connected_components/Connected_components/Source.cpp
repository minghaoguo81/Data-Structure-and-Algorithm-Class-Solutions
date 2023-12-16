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

int num_components(vector<vector<int> >& adj) 
{
	int n_vertices = adj.size();
	if (n_vertices == 0)
		return 0;


	vector<int> group(n_vertices, 0);

	int group_count = 1;

	for (size_t i = 0; i < n_vertices; i++)
	{
		if (group[i] == 0)
		{
			explore(adj, group, group_count, i);
			group_count++;
		}
	}

	return --group_count;
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

	cout << num_components(adj) << endl;

	return 0;
}