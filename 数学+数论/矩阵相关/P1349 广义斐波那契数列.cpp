/*
========= Plozia =========
	Author:Plozia
	Problem:P1349 广义斐波那契数列
	Date:2021/6/8
========= Plozia =========
*/

#include <bits/stdc++.h>
#define int long long

typedef long long LL;
// const int MAXN = ;
int p, q, a1, a2, n, m;
struct Matrix
{
	LL a[5][5];
	int r, c;
	Matrix operator *(const Matrix &fir)
	{
		Matrix tmp; memset(tmp.a, 0, sizeof(tmp.a));
		tmp.r = r; tmp.c = fir.c;
		for (int i = 1; i <= r; ++i)
			for (int k = 1; k <= c; ++k)
			{
				int t = a[i][k];
				for (int j = 1; j <= fir.c; ++j)
					{ tmp.a[i][j] += t * fir.a[k][j]; tmp.a[i][j] %= m; }
			}
		return tmp;
	}
}d, f;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

Matrix ksm(Matrix a, LL b, LL p)
{
	Matrix ans; memset(ans.a, 0, sizeof(ans.a));
	ans.r = ans.c = a.r;
	for (int i = 1; i <= a.r; ++i) ans.a[i][i] = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) ans = ans * a;
	return ans;
}

signed main()
{
	p = Read(), q = Read(), a1 = Read(), a2 = Read(), n = Read(), m = Read();
	a1 %= m, a2 %= m; f.a[1][1] = a1, f.a[1][2] = a2; f.r = 1, f.c = 2;
	if (n == 1 || n == 2)
	{
		if (n == 1) printf("%d\n", a1);
		if (n == 2) printf("%d\n", a2);
		return 0;
	}
	n -= 2;
	d.a[1][1] = 0; d.a[1][2] = q; d.a[2][1] = 1; d.a[2][2] = p;
	d.r = 2; d.c = 2; d = ksm(d, n, m);
	f = f * d; printf("%lld\n", f.a[1][2]); return 0;
}