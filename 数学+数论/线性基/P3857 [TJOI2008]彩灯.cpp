/*
========= Plozia =========
	Author:Plozia
	Problem:P3857 [TJOI2008]彩灯
	Date:2021/7/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 55;
int n, m;
LL a[MAXN], d[MAXN], cnt;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Add(LL x)
{
	for (int i = 50; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (d[i] & x) x = x ^ d[i];
			else { d[i] = x; ++cnt; return ; }
		}
	}
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			char ch; std::cin >> ch;
			a[i] = (a[i] << 1) + (LL)(ch == 'O');
		}
	}
	for (int i = 1; i <= n; ++i) Add(a[i]);
	printf("%lld\n", (1ll << cnt) % 2008); return 0;
}