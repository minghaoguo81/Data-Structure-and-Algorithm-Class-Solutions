#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <stack>

using namespace std;

vector<string> EulerCycle(map<string, set<string>> graph)
{
    stack<string> verteces;
    vector<string> path;
    verteces.push(graph.begin()->first);
    string current = verteces.top();

    while (not verteces.empty())
    {
        current = verteces.top();
        if (not graph[current].empty())
        {
            verteces.push(*graph[current].begin());
            graph[current].erase(graph[current].begin());
            continue;
        }
        path.push_back(current);
        verteces.pop();
    }

    reverse(path.begin(), path.end());
    return path;
}

map<string, set<string>>
construct_DeBruijn_graph(const int k, const int n)
{
    map<string, set<string>> graph;

    for (size_t i = 0; i < n; ++i)
    {
        auto s1 = bitset<16>{ i }.to_string().substr(16 - k, k - 1);
        auto s2 = bitset<16>{ i * 2 % n }.to_string().substr(16 - k);
        auto s3 = bitset<16>{ i * 2 % n + 1 }.to_string().substr(16 - k);

        graph[s1].emplace(s2.substr(0, k - 1));
        graph[s1].emplace(s3.substr(0, k - 1));
    }

    return graph;
}

void print_kUniversal_Circular_String(const vector<string>& cycle, const int k)
{
    for (int i = 0; i < cycle.size() - 1; ++i)
    {
        const auto& s = cycle[i];
        cout << s.substr(0, s.size() - (k - 2));
    }
    cout << endl;
}

int main()
{
    int k;
    cin >> k;
    int n = pow(2, k);

    const auto cycle = EulerCycle(construct_DeBruijn_graph(k, n));
    print_kUniversal_Circular_String(cycle, k);

    return 0;
}
