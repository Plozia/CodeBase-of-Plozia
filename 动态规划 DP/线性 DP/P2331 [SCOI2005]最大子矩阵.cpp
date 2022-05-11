/*
========= Plozia =========
	Author:Plozia
	Problem:P2331 [SCOI2005]最大子矩阵
	Date:2021/11/23
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5, MAXM = 2 + 5, MAXK = 10 + 5;
int n, m, k, f[MAXN][MAXN][MAXK], a[MAXN][MAXM], sum[3][MAXN];

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
	n = Read(), m = Read(), k = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = Read();
	for (int j = 1; j <= m; ++j)
		for (int i = 1; i <= n; ++i)
			sum[j][i] = sum[j][i - 1] + a[i][j];
	for (int l = 1; l <= k; ++l)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
			{
				f[i][j][l] = -0x7f7f7f7f;
				f[i][j][l] = Max(f[i][j][l], Max(f[i - 1][j][l], f[i][j - 1][l]));
				for (int p = 0; p <= i; ++p)
					f[i][j][l] = Max(f[i][j][l], f[p][j][l - 1] + sum[1][i] - sum[1][p]);
				for (int p = 0; p <= j; ++p)
					f[i][j][l] = Max(f[i][j][l], f[i][p][l - 1] + sum[2][j] - sum[2][p]);
				if (i != j) continue ;
				for (int p = 0; p <= i; ++p)
					f[i][j][l] = Max(f[i][j][l], f[p][p][l - 1] + sum[1][i] - sum[1][p] + sum[2][j] - sum[2][p]);
			}
	printf("%d\n", f[n][n][k]); return 0;
}
