/*
========= Plozia =========
	Author:Plozia
	Problem:P1169 [ZJOI2007]ÆåÅÌÖÆ×÷
	Date:2021/3/13
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2000 + 10;
int n, m, a[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN], Up[MAXN][MAXN], ans1, ans2;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
int Max(int fir, int sec) {return (fir > sec) ? fir : sec;}
int Min(int fir, int sec) {return (fir < sec) ? fir : sec;}

void Reverse()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = !a[i][j];
}

void Getans()
{
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	memset(Up, 0, sizeof(Up));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (a[i][j]) l[i][j] = r[i][j] = j, Up[i][j] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 2; j <= m; ++j)
			if (a[i][j] && a[i][j - 1]) l[i][j] = l[i][j - 1];
	for (int i = 1; i <= n; ++i)
		for (int j = m - 1; j >= 1; --j)
			if (a[i][j] && a[i][j + 1]) r[i][j] = r[i][j + 1];
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (a[i][j] && a[i - 1][j]) Up[i][j] = Up[i - 1][j] + 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if ((i ^ 1) && a[i][j] && a[i - 1][j])
			{
				l[i][j] = Max(l[i][j], l[i - 1][j]);
				r[i][j] = Min(r[i][j], r[i - 1][j]);
			}
			ans1 = Max(ans1, Min(r[i][j] - l[i][j] + 1, Up[i][j]) * Min(r[i][j] - l[i][j] + 1, Up[i][j]));
			ans2 = Max(ans2, (r[i][j] - l[i][j] + 1) * Up[i][j]);
		}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if ((i ^ j) & 1) a[i][j] = !a[i][j];
	Getans(); Reverse(); Getans();
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
