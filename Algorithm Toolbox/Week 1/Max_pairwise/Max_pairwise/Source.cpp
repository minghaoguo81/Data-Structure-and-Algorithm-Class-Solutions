#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long MaxPairWiseProduct(const vector<int>& numbers)
{
	int n = numbers.size();

	long long result = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if ((long long)numbers[i] * numbers[j] > result)
			{
				result = max(result, (long long)numbers[i] * numbers[j]);
			}
		}
	}

	return result;
}

long long MaxPairwiseProductFast(const vector<int>& numbers)
{
	int n = numbers.size();

	int max_index1 = -1;
	for (int i = 0; i < n; ++i)
		if ((max_index1 == -1) || (numbers[i] > numbers[max_index1]))
			max_index1 = i;

	int max_index2 = -1;
	for (int j = 0; j < n; ++j)
		if ((j != max_index1) && ((max_index2 == -1) || (numbers[j] > numbers[max_index2])))
			max_index2 = j;

	return ((long long)(numbers[max_index1])) * numbers[max_index2];
}


int main()
{
	int n;
	cin >> n;
	vector<int> numbers(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> numbers[i];
	}

	long long result = MaxPairwiseProductFast(numbers);
	cout << result << endl;

	return 0;
}