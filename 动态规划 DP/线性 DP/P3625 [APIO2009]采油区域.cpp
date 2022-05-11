/*
========= Plozia =========
	Author:Plozia
	Problem:P3625 [APIO2009]采油区域
	Date:2021/5/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1500 + 10;
int n, m, k, a[MAXN][MAXN], sum[MAXN][MAXN], f[MAXN][MAXN][4], Line[MAXN][MAXN], Col[MAXN][MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Get(int r1, int c1, int r2, int c2)
{
	if (r1 > r2) std::swap(r1, r2); if (c1 > c2) std::swap(c1, c2);
	return sum[r2][c2] - sum[r2][c1 - 1] - sum[r1 - 1][c2] + sum[r1 - 1][c1 - 1];
}

void init()
{
	f[k][k][0] = Get(1, 1, k, k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (i > k) { f[i][j][0] = Max(f[i][j][0], f[i - 1][j][0]); }
			if (j > k) { f[i][j][0] = Max(f[i][j][0], f[i][j - 1][0]); }
			if (i - k + 1 > 0 && j - k + 1 > 0) { f[i][j][0] = Max(f[i][j][0], Get(i - k + 1, j - k + 1, i, j)); }
		}
	f[k][m - k + 1][1] = Get(1, m - k + 1, k, m);
	for (int i = 1; i <= n; ++i)
		for (int j = m; j >= 1; --j)
		{
			if (i > k) { f[i][j][1] = Max(f[i][j][1], f[i - 1][j][1]); }
			if (j < m - k + 1) { f[i][j][1] = Max(f[i][j][1], f[i][j + 1][1]); }
			if (i - k + 1 > 0 && j + k - 1 <= m) { f[i][j][1] = Max(f[i][j][1], Get(i - k + 1, j, i, j + k - 1)); }
		}
	f[n - k + 1][k][2] = Get(n - k + 1, 1, n, k);
	for (int i = n; i >= 1; --i)
		for (int j = 1; j <= m; ++j)
		{
			if (i < n - k + 1) { f[i][j][2] = Max(f[i][j][2], f[i + 1][j][2]); }
			if (j > k) { f[i][j][2] = Max(f[i][j][2], f[i][j - 1][2]); }
			if (i + k - 1 <= n && j - k + 1 > 0) { f[i][j][2] = Max(f[i][j][2], Get(i, j - k + 1, i + k - 1, j)); }
		}
	f[n - k + 1][m - k + 1][3] = Get(n - k + 1, m - k + 1, n, m);
	for (int i = n; i >= 1; --i)
		for (int j = m; j >= 1; --j)
		{
			if (i < n - k + 1) { f[i][j][3] = Max(f[i][j][3], f[i + 1][j][3]); }
			if (j < m - k + 1) { f[i][j][3] = Max(f[i][j][3], f[i][j + 1][3]); }
			if (i + k - 1 <= n && j + k - 1 <= m) { f[i][j][3] = Max(f[i][j][3], Get(i, j, i + k - 1, j + k - 1)); }
		}
}

int main()
{
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	init();
	for (int i = 1; i + k - 1 <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (j >= k) { Line[i][i + k - 1] = Max(Line[i][i + k - 1], Get(i, j - k + 1, i + k - 1, j)); }
			if (j + k - 1 <= m) { Line[i][i + k - 1] = Max(Line[i][i + k - 1], Get(i, j, i + k - 1, j + k - 1)); }
		}
	}
	for (int len = k + 1; len <= n; ++len)
	{
		for (int i = 1; i <= n; ++i)
		{
			int j = i + len - 1; if (j > n) break ;
			Line[i][j] = Max(Line[i + 1][j], Line[i][j - 1]);
		}
	}
	for (int j = 1; j + k - 1 <= m; ++j)
	{
		for (int i = 1; i <= n; ++i)
		{
			if (i >= k) { Col[j][j + k - 1] = Max(Col[j][j + k - 1], Get(i - k + 1, j, i, j + k - 1)); }
			if (i + k - 1 <= n) { Col[j][j + k - 1] = Max(Col[j][j + k - 1], Get(i, j, i + k - 1, j + k - 1)); }
		}
	}
	for (int len = k + 1; len <= m; ++len)
	{
		for (int i = 1; i <= m; ++i)
		{
			int j = i + len - 1; if (j > m) break ;
			Col[i][j] = Max(Col[i + 1][j], Col[i][j - 1]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			ans = Max(ans, Col[1][j - 1] + f[i][j][1] + f[i + 1][j][3]);
			ans = Max(ans, Col[j + 1][m] + f[i][j][0] + f[i + 1][j][2]);
			ans = Max(ans, f[i][j][0] + f[i][j + 1][1] + Line[i + 1][n]);
			ans = Max(ans, f[i][j][2] + f[i][j + 1][3] + Line[1][i - 1]);
		}
	for (int i = k; i <= n - k + 1; ++i)
		for (int j = i + k - 1; j <= n - k + 1; ++j)
			ans = Max(ans, Line[1][i] + Line[i + 1][j - 1] + Line[j][n]);
	for (int i = k; i <= m - k + 1; ++i)
		for (int j = i + k - 1; j <= m - k + 1; ++j)
			ans = Max(ans, Col[1][i] + Col[i + 1][j - 1] + Col[j][m]);
	printf("%d\n", ans); return 0;
}