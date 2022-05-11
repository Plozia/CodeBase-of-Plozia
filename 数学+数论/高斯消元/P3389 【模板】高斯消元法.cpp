/*
========= Plozia =========
	Author:Plozia
	Problem:P3389 【模板】高斯消元法
	Date:2021/7/11
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
typedef double db;
const int MAXN = 100 + 5;
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
	for (int i = 1; i <= n; ++i)
	{
		int m = i;
		for (int j = i + 1; j <= n; ++j)
			if (fabs(a[j][i]) > fabs(a[m][i])) m = j;
		if (i != m) std::swap(a[i], a[m]);
		if (fabs(a[i][i]) < eps) { printf("No Solution\n"); return 0; }
		for (int j = 1; j <= n; ++j)
		{
			if (j != i)
			{
				db d = a[j][i] / a[i][i];
				for (int k = i + 1; k <= n + 1; ++k)
					a[j][k] -= a[i][k] * d;
			}
		}
	}
	for (int i = 1; i <= n; ++i) printf("%.2lf\n", a[i][n + 1] / a[i][i]); return 0;
}