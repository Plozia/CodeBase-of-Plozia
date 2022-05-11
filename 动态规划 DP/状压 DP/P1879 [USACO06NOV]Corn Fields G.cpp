/*
========= Plozia =========
	Author:Plozia
	Problem:P1879 [USACO06NOV]Corn Fields G
	Date:2021/5/27
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 12 + 5, P = 1e8 + 10;
int n, m, cnt, c[400], Map[MAXN];
LL f[MAXN][400];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void dfs(int now, int sum)
{
	if (now >= m) { ++cnt; c[cnt] = sum; return ; }
	dfs(now + 1, sum);
	dfs(now + 2, sum + (1 << now));
}

int main()
{
	n = Read(), m = Read();
	dfs(0, 0);
	for (int i = 1; i <= n; ++i)
	{
		LL sum = 0;
		for (int j = m; j >= 1; --j) sum += Read() * (1 << (j - 1));
		Map[i] = sum;
	}
	for (int i = 1; i <= cnt; ++i)
		if ((Map[1] & c[i]) == c[i]) f[1][i] = 1;
	for (int i = 2; i <= n; ++i)
		for (int k = 1; k <= cnt; ++k)
		{
			if ((Map[i] & c[k]) != c[k]) continue ;
			for (int j = 1; j <= cnt; ++j)
			{
				if ((Map[i - 1] & c[j]) != c[j]) continue ;
				if ((c[j] & c[k]) != 0) continue ;
				f[i][k] = (f[i][k] + f[i - 1][j]) % P;
			}
		}
	LL ans = 0;
	for (int i = 1; i <= cnt; ++i)
		if ((Map[n] & c[i]) == c[i]) ans = (ans + f[n][i]) % P;
	printf("%lld\n", ans); return 0;
}