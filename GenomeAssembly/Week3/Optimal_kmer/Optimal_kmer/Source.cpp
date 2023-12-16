#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>

using namespace std;

enum class result
{
    no_cycle,
    one_cycle,
    multiple_cycles
};

result check_Euler_cycle(const map<string, set<string>> graph)
{
    for (auto& kv : graph)
    {
        if (kv.second.empty())
            return result::no_cycle;
        if (kv.second.size() > 1)
            return result::multiple_cycles;
    }

    return result::one_cycle;
}

map<string, set<string>>
construct_DeBruijn_graph(const vector<string>& reads, const int k)
{
    map<string, set<string>> graph;

    for (const auto& read : reads)
    {
        for (size_t i = 0; i + k < read.size(); ++i)
        {
            graph[read.substr(i, k - 1)].emplace(read.substr(i + 2, k - 1));
            if (i + k + 1 < read.size())
                graph[read.substr(i + 2, k - 1)];
        }
    }

    return graph;
}

vector<string> read_input()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string s;

    while (cin >> s)
        reads.emplace_back(move(s));

    return reads;
}

int bs_k(const vector<string> reads, int l, int r)
{
    while (r >= l)
    {
        int mid = l + (r - l) / 2;

        result res = check_Euler_cycle(construct_DeBruijn_graph(reads, mid));
        switch (res)
        {
        case result::one_cycle:
            return mid;
        case result::no_cycle:
            r = mid - 1;
            continue;
        case result::multiple_cycles:
            l = mid + 1;
            continue;
        }
    }

    throw logic_error{ "optimal k not found" };
}

int main()
{
    const int mer_size = 100;
    cout << bs_k(read_input(), 0, mer_size) << endl;

    return 0;
}