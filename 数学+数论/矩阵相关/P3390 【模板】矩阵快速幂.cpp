/*
========= Plozia =========
	Author:Plozia
	Problem:P3390 【模板】矩阵快速幂
	Date:2021/6/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 10, P = 1e9 + 7;
int n;
LL k;

struct Matrix
{
	LL a[MAXN][MAXN];
	Matrix operator *(const Matrix &fir)
	{
		Matrix c; memset(c.a, 0, sizeof(c.a));
		for (int i = 1; i <= n; ++i)
			for (int k = 1; k <= n; ++k)
			{
				int r = a[i][k];
				for (int j = 1; j <= n; ++j) { c.a[i][j] += r * fir.a[k][j]; c.a[i][j] %= P; }
			}
		return c;
	}
}a;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

Matrix ksm(Matrix a, LL b, LL p)
{
	Matrix ans;
	for (int i = 1; i <= n; ++i)
			ans.a[i][i] = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) ans = ans * a;
	return ans;
}

int main()
{
	n = Read(), k = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			a.a[i][j] = Read();
	Matrix ans = ksm(a, k, P);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j) printf("%lld ", ans.a[i][j]);
		printf("\n");
	}
	return 0;
}