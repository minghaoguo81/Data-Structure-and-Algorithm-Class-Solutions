#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs2(vector<int>& a, vector<int>& b) 
{
    return min(std::min(a.size(), b.size()));
}

int main() 
{
    size_t n;
    cin >> n;
    vector<int> a(n);

    for (size_t i = 0; i < n; i++) {
        cin >> a[i];
    }

    size_t m;
    cin >> m;
    vector<int> b(m);

    for (size_t i = 0; i < m; i++) {
        cin >> b[i];
    }

    cout << lcs2(a, b) << endl;

    return 0;
}