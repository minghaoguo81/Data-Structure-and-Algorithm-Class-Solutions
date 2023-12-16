#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define NOT_EXPLORED 0
#define BEING_EXPLORED 1
#define USED 2

void dfs(vector<vector<int> >& adj, vector<int>& used, vector<int>& order, int x) 
{
	if (used[x] == USED)
		return;

	used[x] = BEING_EXPLORED;

	for (size_t i = 0; i < adj[x].size(); i++)
	{
		dfs(adj, used, order, adj[x][i]);
	}

	order.push_back(x);
	used[x] = USED;
	return;
}

vector<int> Toposort(vector<vector<int> > adj) 
{
	int n_vertices = adj.size();
	vector<int> used(n_vertices, NOT_EXPLORED);
	vector<int> order;

	for (size_t i = 0; i < n_vertices; i++)
	{
		dfs(adj, used, order, i);

	}

	return order;
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
	vector<int> order = Toposort(adj);

	for (int i = order.size() - 1; i >= 0; --i) 
	{
		cout << order[i] + 1 << " ";
	}
	cout << endl;

	return 0;
}