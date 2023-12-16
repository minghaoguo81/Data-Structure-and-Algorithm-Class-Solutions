#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>

using namespace std;

bool check_dgs(const vector<int>& in, const vector<int>& out)
{
    assert(in.size() == out.size());
    for (size_t i = 0; i < in.size(); ++i)
        if (in[i] != out[i])
            return false;
    return true;
}

vector<int> make_ec(vector<vector<int>> graph)
{
    stack<int> vt;
    vector<int> path;
    vt.push(0);
    int ct = 0;

    while (not vt.empty())
    {
        ct = vt.top();
        if (not graph[ct].empty())
        {
            vt.push(graph[ct].back());
            graph[ct].pop_back();
            continue;
        }
        path.push_back(ct);
        vt.pop();
    }

    reverse(path.begin(), path.end());
    path.pop_back();
    return path;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int num_vt, num_ed;

    cin >> num_vt >> num_ed;

    vector<vector<int>> graph(num_vt);

    vector<int> in(num_vt), out(num_vt);

    for (int i = 0; i < num_ed; ++i)
    {
        int from, to;
        cin >> from >> to;
        graph[--from].push_back(--to);
        ++in[to];
        ++out[from];
    }

    if (not check_dgs(in, out))
    {
        cout << 0 << endl;
        return 0;
    }

    auto cycle = make_ec(move(graph));

    cout << 1 << '\n';
    for (auto v : cycle)
        cout << v + 1 << ' ';
    cout << endl;

    return 0;
}