#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

vector<string>
EulerCycle(map<string, vector<string>> graph)
{
    stack<string> verteces;
    vector<string> path;
    path.reserve(graph.size());
    verteces.push(graph.begin()->first);
    string current = verteces.top();

    while (not verteces.empty())
    {
        current = verteces.top();
        if (not graph[current].empty())
        {
            verteces.push(move(graph[current].back()));
            graph[current].pop_back();
            continue;
        }
        path.emplace_back(move(current));
        verteces.pop();
    }

    reverse(path.begin(), path.end());
    return path;
}

map<string, vector<string>>
construct_DeBruijn_graph()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    map<string, vector<string>> graph;

    while (cin >> s)
        graph[s.substr(0, s.size() - 1)].emplace_back(s.substr(1));

    return graph;
}

void print_genome(const vector<string>& cycle)
{
    cout << cycle.front();
    for (size_t i = 1; i < cycle.size() - 9; ++i)
        cout << cycle[i].back();
    cout << endl;
}

int main()
{
    print_genome(EulerCycle(construct_DeBruijn_graph()));

    return 0;
}
