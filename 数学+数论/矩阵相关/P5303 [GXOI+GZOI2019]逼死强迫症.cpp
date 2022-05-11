/*
========= Plozia =========
	Author:Plozia
	Problem:P5303 [GXOI/GZOI2019]逼死强迫症
	Date:2021/6/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 10;
const LL P = 1e9 + 7;
int n, t;
struct Matrix
{
	LL a[MAXN][MAXN];
	int r, c;
	void init()
	{
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= r; ++i) a[i][i] = 1;
	}
	Matrix operator *(Matrix &fir)
	{
		Matrix tmp; tmp.r = r; tmp.c = fir.c; memset(tmp.a, 0, sizeof(tmp.a));
		for (int i = 1; i <= r; ++i)
			for (int k = 1; k <= c; ++k)
			{
				LL t = a[i][k];
				for (int j = 1; j <= fir.c; ++j)
					{ ((tmp.a[i][j] += t * fir.a[k][j]) >= P) ? (tmp.a[i][j] %= P) : 0; }
			}
		return tmp;
	}
}Base, Begin;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Deal()
{
	Begin.r = 1; Begin.c = 3;
	Begin.a[1][1] = Begin.a[1][2] = 1; Begin.a[1][3] = 2;
	Base.r = Base.c = 3;
	Base.a[1][2] = Base.a[1][3] = Base.a[2][1] = Base.a[2][2] = Base.a[2][3] = Base.a[3][3] = 1;
}

Matrix ksm(Matrix fir, LL sec)
{
	Matrix ans; ans.r = ans.c = fir.r; ans.init();
	for (; sec; sec >>= 1, fir = fir * fir)
		if (sec & 1) ans = ans * fir;
	return ans;
}

int main()
{
	t = Read();
	while (t--)
	{
		n = Read(); LL sum1, sum2, sum3; Matrix Plozia;
		if (n < 3) printf("0\n");
		else if (n == 3) printf("2\n");
		Deal(); Plozia = ksm(Base, n - 4); Begin = Begin * Plozia; sum1 = Begin.a[1][3];
		Deal(); Plozia = ksm(Base, n - 1); Begin = Begin * Plozia; sum2 = Begin.a[1][3];
	}
	return 0;
}