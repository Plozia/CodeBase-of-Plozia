/*
========= Plozia =========
	Author:Plozia
	Problem:
	Date:
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 100 + 5, MAXM = 1e4 + 5;
int n, m, f[MAXN][MAXN], g[MAXM], a[MAXN][MAXN], cnt[MAXN], sum[MAXN][MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i)
	{
		cnt[i] = Read();
		for (int j = 1; j <= cnt[i]; ++j) a[i][j] = Read();
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= cnt[i]; ++j)
			sum[i][j] = sum[i][j - 1] + a[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= cnt[i]; ++j)
			for (int k = 0; k <= j; ++k)
				f[i][j] = Max(f[i][j], sum[i][k] + sum[i][cnt[i]] - sum[i][cnt[i] - (j - k)]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= cnt[i]; ++j)
			std::cerr << f[i][j] << " \n"[j == cnt[i]];
	for (int i = 1; i <= n; ++i)
	{
		for (int j = m; j >= 1; --j)
			for (int k = 0; k <= cnt[i]; ++k)
				if (j >= k) g[j] = Max(g[j], g[j - k] + f[i][k]);
	}
	printf("%d\n", g[m]); return 0;
}