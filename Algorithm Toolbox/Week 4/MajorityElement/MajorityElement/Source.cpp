#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int major_ele(vector<int>& a, int left, int right) 
{
	sort(a.begin(), a.end());

	int element = a[0];
	int ct = 1;
	int major = int(a.size() / 2);
	for (size_t i = 1; (i < a.size() && ct <= major); i++)
	{
		if (a[i] == element)
			ct++;
		else
		{
			element = a[i];
			ct = 1;
		}
	}
	return (ct > major);

}

int main() 
{
	int n;
	cin >> n;
	vector<int> a(n);

	for (size_t i = 0; i < a.size(); ++i) {
		cin >> a[i];
	}

	cout << major_ele(a, 0, a.size()) << endl;

	return 0;
}