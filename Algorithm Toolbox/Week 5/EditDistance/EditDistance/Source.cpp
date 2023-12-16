#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int ed_dist(const string& str1, const string& str2) 
{
	vector<vector<int>> D((str1.length() + 1),vector<int>(str2.length() + 1));

	for (size_t i = 0; i < str1.length() + 1; i++)
	{
		D[i][0] = i;
	}
	for (size_t j = 0; j < str2.length() + 1; j++)
	{
		D[0][j] = j;
	}


	for (size_t i = 1; i < str1.length() + 1; i++)
	{
		for (size_t j = 1; j < str2.length() + 1; j++)
		{
			if (str1[i - 1] == str2[j - 1]) {
				D[i][j] = D[i - 1][j - 1];
			}
			else {
				D[i][j] = min(min(D[i][j - 1], D[i - 1][j - 1]), D[i - 1][j]) + 1;
			}
		}
	}

	return D[str1.length()][str2.length()];
}

int main() 
{
	string str1;
	string str2;

	cin >> str1 >> str2;
	cout << ed_dist(str1, str2) << endl;

	return 0;
}