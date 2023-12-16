#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int overlap(const string& a, const string& b, const int mer) noexcept
{
    for (int i = 0, n = 1 + a.size() - mer; i < n; ++i)
    {
        if (strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0)
            return a.size() - i;
    }

    return 0;
}

string assembly(vector<string> rds, const int mer) noexcept
{
    string gme;
    gme.reserve(1000);
    gme += rds.front();

    string first_read = rds.front(), cur_read = "";
    int cur_index = 0;

    while (rds.size() > 1)
    {
        cur_read = move(rds[cur_index]);
        rds.erase(rds.begin() + cur_index);

        int max_overlap = -1;

        for (int j = 0; j < rds.size(); ++j)
        {
            int overlap_x = overlap(cur_read, rds[j], mer);
            if (overlap_x > max_overlap)
                max_overlap = overlap_x, cur_index = j;
        }

        gme += rds[cur_index].substr(max_overlap);
    }

    gme.erase(0, overlap(rds[0], first_read, mer));

    return gme;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> rds;
    rds.reserve(1618);
    string s;

    while (cin >> s)
    {
        if (rds.back() != s)
            rds.emplace_back(move(s));
    }

    cout << assembly(move(rds), 12) << endl;

    return 0;
}