#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) 
{
	vector<int> summands;
	
	int total_candies = 0;

	for (int k = 1; total_candies + k <= n; k++)
	{
		summands.push_back(k);
		total_candies += k;

	}

	int last = summands.size() - 1;

	summands[last] = summands[last] + (n - total_candies);

	return summands;
}

int main() 
{
	int n;
	cin >> n;

	vector<int> summands = optimal_summands(n);

	cout << summands.size() << '\n';

	for (size_t i = 0; i < summands.size(); ++i) 
	{
		cout << summands[i] << ' ';
	}
}