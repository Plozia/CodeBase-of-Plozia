/*
========= Plozia =========
	Author:Plozia
	Problem:CF476D Dreamoon and Sets
	Date:2021/11/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 10000 + 5;
int n, k;

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
	n = Read(), k = Read();
	printf("%lld\n", 1ll * (1ll * 2 + 6 * (n - 1) + 3) * k);
	for (int i = 1; i <= n; ++i)
	{
		LL p = 2 + 1ll * 6 * (i - 1);
		printf("%lld %lld %lld %lld\n", (p - 1) * k, p * k, (p + 1) * k, (p + 3) * k);
	}
	return 0;
}