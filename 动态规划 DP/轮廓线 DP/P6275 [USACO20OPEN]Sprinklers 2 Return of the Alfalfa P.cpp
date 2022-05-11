/*
========= Plozia =========
	Author:Plozia
	Problem:P6275 [USACO20OPEN]Sprinklers 2: Return of the Alfalfa P
	Date:2021/11/16
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e3 + 5;
const LL P = 1e9 + 7;
int n, a[MAXN][MAXN], sum[MAXN], Pow[MAXN], f[MAXN][MAXN][2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Add(int fir, int sec) { return (fir + sec >= P) ? (fir + sec - P) : (fir + sec); }
LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}
const LL inv2 = ksm(2);

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			char ch = getchar();
			while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
			if (ch == '.') a[i][j] = 1;
			sum[i] += a[i][j];
		}
	Pow[0] = 1;
	for (int i = 1; i <= n; ++i) Pow[i] = Pow[i - 1] * 2 % P;
	f[0][0][0] = f[0][0][1] = 1;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j)
		{
			if (!i && !j) continue;
			if (j > 0)
			{
				f[i][j][0] = f[i][j - 1][0];
				if (a[i][j] == 1) f[i][j][0] = Add(f[i][j][0], 1ll * f[i][j - 1][1] * inv2 % P);
			}
			if (i > 0)
			{
				f[i][j][1] = 1ll * f[i - 1][j][1] * Pow[sum[i]] % P;
				if (a[i][j] == 1) f[i][j][1] = Add(f[i][j][1], 1ll * f[i - 1][j][0] * Pow[sum[i] - 1] % P);
			}
		}
	printf("%lld\n", (1ll * f[n][n][0] + 1ll * f[n][n][1]) % P); return 0;
}