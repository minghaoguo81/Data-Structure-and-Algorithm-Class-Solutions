#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstring>
#include <climits>
#include <cmath>

using std::vector;
using std::string;
using std::max;
using std::min;

using namespace std;

long long eval(long long a, long long b, char op) 
{
	if (op == '*') 
	{
		return a * b;
	}
	else if (op == '+') 
	{
		return a + b;
	}
	else if (op == '-') 
	{
		return a - b;
	}
	else 
	{
		assert(0);
	}
}

long long max_val(const string& exp)
{
	int length = exp.size();
	const int numOfnum = (length + 1) / 2;

	long long minArray[numOfnum][numOfnum];
	long long maxArray[numOfnum][numOfnum];

	memset(minArray, 0, sizeof(minArray));
	memset(maxArray, 0, sizeof(maxArray));

	for (int i = 0; i < numOfnum; i++)
	{
		minArray[i][i] = std::stoll(exp.substr(2 * i, 1));
		maxArray[i][i] = std::stoll(exp.substr(2 * i, 1));
	}

	for (int s = 0; s < numOfnum - 1; s++)
	{
		for (int i = 0; i < numOfnum - s - 1; i++)
		{
			int j = i + s + 1;
			long long minVal = LLONG_MAX;
			long long maxVal = LLONG_MIN;

			for (int k = i; k < j; k++)
			{
				long long a = eval(minArray[i][k], minArray[k + 1][j], exp[2 * k + 1]);
				long long b = eval(minArray[i][k], maxArray[k + 1][j], exp[2 * k + 1]);
				long long c = eval(maxArray[i][k], minArray[k + 1][j], exp[2 * k + 1]);
				long long d = eval(maxArray[i][k], maxArray[k + 1][j], exp[2 * k + 1]);
				minVal = min(minVal, min(a, min(b, min(c, d))));
				maxVal = max(maxVal, max(a, max(b, max(c, d))));
			}
			minArray[i][j] = minVal;
			maxArray[i][j] = maxVal;
		}
	}

	return maxArray[0][numOfnum - 1];
}

int main() 
{
	string s;
	cin >> s;
	cout << max_val(s) << endl;

	return 0;
}