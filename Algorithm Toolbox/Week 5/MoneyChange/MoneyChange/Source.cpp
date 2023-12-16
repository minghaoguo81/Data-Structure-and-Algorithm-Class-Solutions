#include <iostream>
#include <vector>

using namespace std;

#define INT32_MAX        2147483647;

int coins_change(const int money, const vector<int>& coins) 
{
	int Num = 0;

	vector<int> m_coins(int(money / coins[0]) + 1);
	m_coins[0] = 0;

	for (size_t m = 1; m <= money; m++)
	{
		m_coins[m] = INT32_MAX;

		for (auto c : coins)
		{
			if (m >= c) {
				Num = m_coins[(m - c)] + 1;
				if (Num < m_coins[m])
					m_coins[m] = Num;
			}
		}
	}
	return m_coins[money];
}

int main() 
{
	int money;
	cin >> money;
	vector<int> coins = { 1, 3, 4 }; 
	//sort(coins.begin(), coins.end());

	cout << coins_change(money, coins) << endl;

	return 0;
}