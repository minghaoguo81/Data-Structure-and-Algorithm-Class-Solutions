#include <iostream>
#include <vector>

using namespace std;

long long countInversions(vector<int>& B, vector<int>& C)
{
	long long inversions = 0;
	for (size_t i = 0; i < B.size(); i++)
	{
		for (size_t j = 0; j < C.size(); j++)
		{
			if (B[i] > C[j])
				inversions++;
		}
	}

	return inversions;
}

long long numberInversion(vector<int>& a) {
	long long inversions = 0;
	if (a.size() == 1) 
		return inversions;

	size_t half = size_t(a.size() / 2) - 1;

	vector<int> B;
	B.insert(B.begin(), a.begin(), a.begin() + half + 1);

	vector<int> C;
	C.insert(C.begin(), a.begin() + half + 1, a.end());

	inversions += numberInversion(B);
	inversions += numberInversion(C);

	inversions += countInversions(B, C);

	return inversions;
}

int main() 
{
	int n;
	cin >> n;
	vector<int> a(n);

	for (size_t i = 0; i < a.size(); i++) 
	{
		cin >> a[i];
	}

	cout << numberInversion(a) << endl;

	return 0;
}