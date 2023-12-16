#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool isSubsetSum(vector<int>& wi, int n, int sum)
{
	if (sum == 0)
		return true;
	if (n == 0 && sum != 0)
		return false;

	if (wi[n - 1] > sum)
		return isSubsetSum(wi, n - 1, sum);

	return isSubsetSum(wi, n - 1, sum) ||
		isSubsetSum(wi, n - 1, sum - wi[n - 1]);
}

int partition3(vector<int>& wi) {

	int W = accumulate(wi.begin(), wi.end(), 0);
	if (W % 3 > 0) return 0;

	return isSubsetSum(wi, wi.size(), W / 3);;
}

int op_souvenirs(int w, int i, vector<int>& wi, vector<vector<int>>& opt_value, vector<vector<bool>>& calculated) {

	if (calculated[w][i]) 
		return opt_value[w][i];
	if ((w % 3 > 0) || (w < 3) || (i < 3)) 
		return 0;

	int val_pos1 = op_souvenirs(w, i - 1, wi, opt_value, calculated);

	int val_pos2 = 0;
	if (w >= wi[i - 1]) 
	{
		val_pos2 = ((op_souvenirs(w - wi[i - 1], i, wi, opt_value, calculated) + wi[i - 1]) % 3 == 0);
	}

	opt_value[w][i] = (val_pos1 || val_pos2);
	calculated[w][i] = true;

	return opt_value[w][wi.size()];
}

int main2() 
{
	int n;
	cin >> n;

	vector<int> wi(n);

	for (size_t i = 0; i < wi.size(); ++i) 
	{
		cin >> wi[i];
	}

	int W = accumulate(wi.begin(), wi.end(), 0);

	vector<vector<int>> opt_value(W + 1, vector<int>(wi.size() + 1));
	vector<vector<bool>> calculated(W + 1, vector<bool>(wi.size() + 1));

	for (size_t i = 0; i < W + 1; i++)
	{
		opt_value[i][0] = 0;
		calculated[i][0] = 1;
	}
	for (size_t j = 0; j < wi.size() + 1; j++)
	{
		opt_value[0][j] = 0;
		calculated[0][j] = 1;
	}

	cout << op_souvenirs(W, n, wi, opt_value, calculated) << endl;

	return 0;
}

int main() 
{
	int n;
	cin >> n;

	vector<int> wi(n);

	for (size_t i = 0; i < wi.size(); ++i) 
	{
		cin >> wi[i];
	}

	cout << partition3(wi) << endl;

	return 0;
}