/*
========= Plozia =========
	Author:Plozia
	Problem:P3811 【模板】乘法逆元
	Date:2021/6/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e6 + 5;
int n;
LL p, inv[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read(), p = Read(); inv[1] = 1;
	for (int i = 2; i <= n; ++i) inv[i] = (p - p / i) * inv[p % i] % p;
	for (int i = 1; i <= n; ++i) printf("%lld\n", inv[i]);
	return 0;
}