/*
========= Plozia =========
	Author:Plozia
	Problem:CF710E Generate a String
	Date:2021/6/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e7 + 5;
int n, x, y;
LL f[MAXN * 2 + 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read(), x = Read(), y = Read();
	for (int i = 1; i <= (n << 1); ++i)
	{
		if (i & 1) f[i] = Min(f[i - 1] + 1ll * x, f[(i + 1) >> 1] + 1ll * x + 1ll * y);
		else f[i] = Min(f[i - 1] + x, f[i >> 1] + y);
	}
	printf("%lld\n", f[n]);
	return 0;
}