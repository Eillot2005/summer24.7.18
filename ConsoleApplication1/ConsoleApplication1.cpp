//杭州电子科技大学-1500

#include<iostream>
using namespace std;
int dp[5001][1001];
int len[5001];
int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int k, n;//客人人数和筷子数量
		cin >> k >> n;
		k += 8;
		for (int j = n; j >= 1; j--)
		{
			cin >> len[j];
		}
		for (int j = 1; j <= n; j++)
		{
			for (int s = 1; s <= k; s++)
			{
				if (j < s * 3)
				{
					dp[j][s] = 0x3f3f3f;
				}
			}
		}
		for (int j = 3; j <= n; j++)
		{
			for (int s = 1; s <= k; s++)
			{
				if (j >= s * 3)
				{
					dp[j][s] = min(dp[j - 1][s], dp[j - 2][s - 1] + (len[j] - len[j - 1]) * (len[j] - len[j - 1]));
				}
				else break;
			}
		}
		cout << dp[n][k] << endl;
	}
}