#include <iostream>
#include <vector>

using namespace std;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) 
{
    vector<int> cnt(points.size());
    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) 
{
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() 
{
    int n, m;
    cin >> n >> m;
    vector<int> starts(n), ends(n);

    for (size_t i = 0; i < starts.size(); i++) 
    {
        cin >> starts[i] >> ends[i];
    }

    vector<int> points(m);

    for (size_t i = 0; i < points.size(); i++) 
    {
        cin >> points[i];
    }

    vector<int> cnt = fast_count_segments(starts, ends, points);

    for (size_t i = 0; i < cnt.size(); i++) 
    {
        cout << cnt[i] << ' ';
    }

    return 0;
}