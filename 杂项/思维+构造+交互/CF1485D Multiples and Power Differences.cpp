/*
========= Plozia =========
	Author:Plozia
	Problem:CF1485D Multiples and Power Differences
	Date:2021/6/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 500 + 5;
int n, m, a[MAXN][MAXN], b[MAXN][MAXN], k[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = Read();
	for (int i = 1; i <= 31; ++i) k[i] = i * i * i * i;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if ((i + j) & 1)
			{
				for (int l = 1; l <= 31; ++l)
				{
					int tmp = 720720 - k[l];
					if (tmp % a[i][j] == 0) { b[i][j] = tmp; break ; }
				}
			}
			else b[i][j] = 720720;
		}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j) printf("%d ", b[i][j]);
		printf("\n");
	}
	return 0;
}