/*
========= Plozia =========
	Author:Plozia
	Problem:P5789 [TJOI2017]可乐（数据加强版）
	Date:2021/6/11
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5, P = 2017;
int n, m, t;

struct Matrix
{
	LL a[MAXN][MAXN];
	int r, c;
	void init()
	{
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= r; ++i) a[i][i] = 1;
	}
	Matrix operator *(const Matrix &fir)
	{
		Matrix tmp; memset(tmp.a, 0, sizeof(tmp.a));
		tmp.r = r; tmp.c = fir.c;
		for (int i = 1; i <= r; ++i)
			for (int k = 1; k <= c; ++k)
			{
				LL t = a[i][k];
				for (int j = 1; j <= fir.c; ++j)
					{ ((tmp.a[i][j] += t * fir.a[k][j]) >= P) ? (tmp.a[i][j] %= P) : 0; }
			}
		return tmp;
	}
}Base;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

Matrix ksm(Matrix fir, LL sec)
{
	Matrix ans; ans.r = ans.c = fir.r; ans.init();
	for (; sec; sec >>= 1, fir = fir * fir)
		if (sec & 1) ans = ans * fir;
	return ans;
}

int main()
{
	n = Read(), m = Read();
	Base.r = Base.c = n + 1; Base.init();
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read();
		Base.a[x][y] = Base.a[y][x] = 1;
	}
	for (int i = 1; i <= n; ++i) Base.a[i][n + 1] = 1;
	t = Read(); Base = ksm(Base, t);
	LL ans = 0;
	for (int i = 1; i <= n + 1; ++i) ans += Base.a[1][i];
	ans %= P; printf("%lld\n", ans); return 0;
}