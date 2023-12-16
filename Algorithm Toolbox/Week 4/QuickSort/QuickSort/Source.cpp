#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

void partition(vector<int>& a, int l, int r, int& m1, int& m2) 
{
	int x = a[l];
	m2 = l;
	int ct_x = 1;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			m2++;
			swap(a[i], a[m2]);
		}
		if (a[i] == x)
		{
			swap(a[l + ct_x], a[m2]);
			ct_x++;
		}
	}

	for (size_t i = 0; i < ct_x; i++)
	{
		swap(a[l + i], a[m2 - i]);
	}

	m1 = m2 - ct_x + 1;
}

void rand_q_sort(vector<int>& a, int l, int r) 
{
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	int m1 = l, m2 = l;
	partition(a, l, r, m1, m2);

	rand_q_sort(a, l, m1 - 1);
	rand_q_sort(a, m2 + 1, r);
}

int main() 
{
	int n;
	cin >> n;
	vector<int> a(n);

	for (size_t i = 0; i < a.size(); ++i) 
	{
		cin >> a[i];
	}

	rand_q_sort(a, 0, a.size() - 1);

	for (size_t i = 0; i < a.size(); ++i) {
		cout << a[i] << ' ';
	}

	return 0;
}