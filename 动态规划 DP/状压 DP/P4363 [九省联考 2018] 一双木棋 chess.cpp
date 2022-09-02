/*
========= Plozia =========
	Author:Plozia
	Problem:P4363 [九省联考2018]一双木棋chess
	Date:2021/8/11
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 15, MAX_State = 1 << 20, INF = 0x7f7f7f7f;
int n, m, a[MAXN][MAXN], b[MAXN][MAXN], f[MAX_State];
bool book[MAX_State];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int dfs(int sta, int who)
{
	if (book[sta]) return f[sta];
	f[sta] = (who == 0) ? -INF : INF; book[sta] = 1;
	int x = 0, y = m;
	for (int i = n + m - 1; i >= 0; --i)
	{
		if (sta & (1 << i)) ++x; else --y;
		if ((sta & (1 << i)) && !(sta & (1 << (i + 1))) && (i != n + m - 1))
		{
			int s = sta ^ (1 << i) ^ (1 << (i + 1));
			if (who == 0) f[sta] = Max(f[sta], dfs(s, who ^ 1) + a[x][y + 1]);
			else f[sta] = Min(f[sta], dfs(s, who ^ 1) - b[x][y + 1]);
		}
	}
	return f[sta];
}
// 纵 1 横 0，先手 0 后手 1
int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			b[i][j] = Read();
	int sta = 0;
	sta = ((1 << n) - 1) << m; book[sta] = 1;
	f[sta] = 0; printf("%d\n", dfs((1 << n) - 1, 0));
	return 0;
}