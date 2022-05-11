/*
========= Plozia =========
	Author:Plozia
	Problem:P4301 [CQOI2013] 新Nim游戏
	Date:2021/7/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5;
int n, a[MAXN], d[40];
LL ans = 0;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

bool Add(int x)
{
	for (int i = 31; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (d[i] & x) x ^= d[i];
			else { d[i] = x; return 0; }
		}
	}
	return 1;
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	std::sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; --i)
		if (Add(a[i])) ans += a[i];
	printf("%lld\n", ans); return 0;
}