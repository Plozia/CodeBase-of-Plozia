/*
========= Plozia =========
	Author:Plozia
	Problem:P2455 [SDOI2006]线性方程组
	Date:2021/7/11
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
typedef double db;
const int MAXN = 50 + 5;
const db eps = 1e-12;
int n;
db a[MAXN][MAXN];

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
	n = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n + 1; ++j)
			scanf("%lf", &a[i][j]);
	int nl = 1;
	for (int i = 1; i <= n; ++i)
	{
		int m = nl;
		for (int j = nl + 1; j <= n; ++j)
			if (fabs(a[j][i]) > fabs(a[m][i])) m = j;
		if (fabs(a[m][i]) < eps) continue ;
		if (nl != m) std::swap(a[nl], a[m]);
		for (int j = 1; j <= n; ++j)
		{
			if (j != nl)
			{
				db d = a[j][i] / a[nl][i];
				for (int k = i + 1; k <= n + 1; ++k)
					a[j][k] -= a[nl][k] * d;
			}
		}
		++nl;
	}
	if (nl <= n)
	{
		while (nl <= n)
		{
			if (a[nl][n + 1] != 0) { printf("-1\n"); return 0; }
			++nl;
		}
		printf("0\n"); return 0;
	}
	for (int i = 1; i <= n; ++i) printf("x%d=%.2lf\n", i, a[i][n + 1] / a[i][i]); return 0;
}