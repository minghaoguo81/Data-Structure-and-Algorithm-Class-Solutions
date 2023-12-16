#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool IsGreaterOrEqual(const string s, const string maxDigit) 
{
	string concat1 = s + maxDigit;
	string concat2 = maxDigit + s;

	return (concat1.compare(concat2) >= 0);
}

string largest_number(vector<string> a) 
{
	stringstream ret;

	while (!a.empty()) 
	{
		int maxDigit_idx = 0;
		for (int i = 1; i < a.size(); i++)
		{
			if (IsGreaterOrEqual(a[i], a[maxDigit_idx]))
				maxDigit_idx = i;
		}
		ret << a[maxDigit_idx];
		a.erase(a.begin() + maxDigit_idx, a.begin() + maxDigit_idx + 1);
	}

	string result;
	ret >> result;
	return result;
}

int main() 
{
	int n;
	cin >> n;

	vector<string> a(n);

	for (size_t i = 0; i < a.size(); i++) 
	{
		cin >> a[i];
	}

	cout << largest_number(a) << endl;
}