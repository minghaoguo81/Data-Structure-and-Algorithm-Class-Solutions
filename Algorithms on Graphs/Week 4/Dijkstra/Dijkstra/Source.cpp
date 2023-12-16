#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MY_MAX_INT 9999999999

int dist(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, int t) 
{
	vector<long long int> distances(adj.size(), MY_MAX_INT);

	auto cmp = [](pair<int, long long int> left, pair<int, long long int> right) { return (((left.second) > (right.second)) || (((left.second) == (right.second)) && ((left.first) > (right.first)))); };
	priority_queue<pair<int, long long int>, vector<pair<int, long long int>>, decltype(cmp)> my_queue(cmp);

	distances[s] = 0;
	my_queue.push(make_pair(s, distances[0]));

	while (!my_queue.empty())
	{
		int vertex_idx = my_queue.top().first;
		int vertex_cost = my_queue.top().second;
		my_queue.pop();

		for (size_t i = 0; i < adj[vertex_idx].size(); i++)
		{

			int dist = distances[vertex_idx] + cost[vertex_idx][i];

			if (distances[adj[vertex_idx][i]] > dist)
			{
				distances[adj[vertex_idx][i]] = dist;
				my_queue.push(make_pair(adj[vertex_idx][i], dist));
			}

		}

	}
	return ((distances[t] < MY_MAX_INT) ? distances[t] : -1);
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

	int s, t;
	cin >> s >> t;
	s--, t--;
	
	cout << dist(adj, cost, s, t) << endl;

	return 0;
}