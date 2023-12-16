#include <iostream>
#include <vector>

using namespace std;

vector<int> sorted_array(vector<int> &a, int size);

int main()
{
	cout << "Enter the numbers of integers in your array: " << endl;
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> sorted_a(n);

	cout << "Enter the integers in your array: " << endl;

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	cout << "Array sorted: " << endl;

	sorted_a = sorted_array(a, n);

	for (int i = 0; i < n; i++)
	{
		cout << sorted_a[i] << " ";
	}

	cout << endl;

	return 0;
}

vector<int> sorted_array(vector<int>& a, int size)
{
	int key;
	int k;

	for (int j = 1; j < size; j++)
	{
		key = a[j];

		k = j - 1;

		while (k >= 0 && a[k] > key)
		{
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}

	return a;
}