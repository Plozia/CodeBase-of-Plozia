/*
========= Plozia =========
	Author:Plozia
	Problem:P3812 【模板】线性基
	Date:2021/6/30
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 50 + 5;
int n;
LL a[MAXN], d[MAXN], ans;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

void add(LL x)
{
	for (int i = 50; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (d[i] & x) x ^= d[i];
			else { d[i] = x; break ; }
		}
	}
}
void Solve() { for (int i = 50; i >= 0; --i) ans = Max(ans, ans ^ d[i]); }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i <= n; ++i) add(a[i]);
	Solve(); printf("%lld\n", ans); return 0;
}