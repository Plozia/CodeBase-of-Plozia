/*
========= Plozia =========
	Author:Plozia
	Problem:P5343 【XR-1】分块
	Date:2021/6/10
========= Plozia =========
*/

#include <bits/stdc++.h>
#define int long long

typedef long long LL;
const int MAXN = 100 + 10, P = 1e9 + 7;
int a[MAXN], PR, aPR[MAXN], NF, aNF[MAXN], cnt, f[MAXN];
LL n;
struct Matrix
{
	int a[MAXN][MAXN], r, c;
	void init()
	{
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= r; ++i)
			a[i][i] = 1;
	}
	Matrix operator *(const Matrix &fir)
	{
		Matrix tmp; memset(tmp.a, 0, sizeof(tmp.a));
		tmp.r = r; tmp.c = fir.c;
		for (int i = 1; i <= r; ++i)
			for (int k = 1; k <= c; ++k)
			{
				int t = a[i][k];
				for (int j = 1; j <= fir.c; ++j)
					{ tmp.a[i][j] += t * fir.a[k][j]; tmp.a[i][j] %= P; }
			}
		return tmp;
	}
}Base;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fh;
}

void init()
{
	int l = 1, r = 1;
	while (l <= PR && r <= NF)
	{
		if (aPR[l] == aNF[r]) { ++l; ++r; ++cnt; a[cnt] = aPR[l - 1]; }
		else if (aPR[l] > aNF[r]) ++r;
		else ++l;
	}
	cnt = std::unique(a + 1, a + cnt + 1) - (a + 1);
	f[0] = 1;
	for (int i = 1; i <= 100; ++i)
		for (int j = 1; j <= cnt; ++j)
		{
			if (i < a[j]) continue ;
			f[i] += f[i - a[j]]; f[i] %= P;
		}
}

Matrix ksm(Matrix fir, LL sec, LL P)
{
	Matrix ans; ans.r = ans.c = fir.r; ans.init();
	for (; sec; sec >>= 1, fir = fir * fir)
		if (sec & 1) ans = ans * fir;
	return ans;
}

signed main()
{
	scanf("%lld", &n); PR = Read();
	for (int i = 1; i <= PR; ++i) aPR[i] = Read();
	NF = Read();
	for (int i = 1; i <= NF; ++i) aNF[i] = Read();
	std::sort(aPR + 1, aPR + PR + 1);
	std::sort(aNF + 1, aNF + NF + 1);
	init(); Base.r = Base.c = 100;
	memset(Base.a, 0, sizeof(Base.a));
	for (int i = 1; i <= 99; ++i) Base.a[i + 1][i] = 1;
	for (int i = 1; i <= cnt; ++i) Base.a[100 - a[i] + 1][100] = 1;
	if (n <= 100) { printf("%d\n", f[n]); return 0; }
	n -= 100; Matrix ans = ksm(Base, n, P);
	Matrix d; memset(d.a, 0, sizeof(d.a));
	d.r = 1; d.c = 100;
	for (int i = 1; i <= 100; ++i) d.a[1][i] = f[i];
	d = d * ans; printf("%d\n", d.a[1][100]); return 0;
}