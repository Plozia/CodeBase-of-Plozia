/*
========= Plozia =========
	Author:Plozia
	Problem:P3624 [APIO2008]DNA
	Date:2021/5/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 50000 + 10;
int n, k, a[MAXN];
LL r, f[MAXN][15][6];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

char Change(int now)
{
	if (now == 1) return 'A';
	if (now == 2) return 'C';
	if (now == 3) return 'G';
	if (now == 4) return 'T';
}

int main()
{
	n = read(), k = read(), r = read();
	for (int i = 1; i <= n; ++i)
	{
		char ch = getchar();
		while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
		if (ch == 'A') a[i] = 1;
		if (ch == 'C') a[i] = 2;
		if (ch == 'G') a[i] = 3;
		if (ch == 'T') a[i] = 4;
	}
	if (a[n] != 0) f[n][1][a[n]] = 1;
	else f[n][1][1] = f[n][1][2] = f[n][1][3] = f[n][1][4] = 1;
	for (int i = n - 1; i >= 1; --i)
	{
		if (a[i])
		{
			for (int j = 1; j <= k; ++j)
				for (int l = 1; l <= 4; ++l)
					f[i][j][a[i]] += f[i + 1][j - (a[i] > l)][l];
		}
		else
		{
			for (int p = 1; p <= 4; ++p)
				for (int j = 1; j <= k; ++j)
					for (int l = 1; l <= 4; ++l)
						f[i][j][p] += f[i + 1][j - (p > l)][l];
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= k; ++j)
			for (int l = 1; l <= 4; ++l)
				f[i][j][l] += f[i][j - 1][l];
	int last = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i]) { printf("%c", Change(a[i])); k -= a[i] < last; last = a[i]; }
		else
		{
			int j;
			for (j = 1; j <= 4 && r > f[i][k - (j < last)][j]; ++j) r -= f[i][k - (j < last)][j];
			printf("%c", Change(j)); k -= (j < last); last = j;
		}
	}
	printf("\n"); return 0;
}