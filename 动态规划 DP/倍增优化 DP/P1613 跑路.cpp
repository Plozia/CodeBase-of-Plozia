/*
========= Plozia =========
	Author:Plozia
	Problem:P1613 跑路
	Date:2021/5/13
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 50 + 10;
int n, m, dis[MAXN][MAXN], g[MAXN][MAXN][70];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = read(), m = read();
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		dis[x][y] = 1; g[x][y][0] = 1;
	}
	for (int t = 1; t <= 64; ++t)
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
				{
					if (g[i][k][t - 1] != 0 && g[k][j][t - 1] != 0)
					{
						g[i][j][t] = 1; dis[i][j] = 1;
					}
				}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				dis[i][j] = Min(dis[i][j], dis[i][k] + dis[k][j]);
	printf("%d\n", dis[1][n]); return 0;
}