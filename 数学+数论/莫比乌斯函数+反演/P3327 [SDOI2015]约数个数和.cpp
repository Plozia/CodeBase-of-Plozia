/*
========= Plozia =========
	Author:Plozia
	Problem:P3327 [SDOI2015]约数个数和
	Date:2022/2/24
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 5;
int t, n, m, Prime[MAXN];
LL mu[MAXN], g[MAXN];
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	book[1] = mu[1] = 1;
	for (int i = 2; i <= 50000; ++i)
	{
		if (!book[i]) { Prime[++Prime[0]] = i; mu[i] = -1; }
		for (int j = 1; j <= Prime[0]; ++j)
		{
			if (i * Prime[j] > 50000) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) { mu[i * Prime[j]] = 0; break ; }
			mu[i * Prime[j]] = -mu[i];
		}
	}
	for (int i = 2; i <= 50000; ++i) mu[i] = mu[i - 1] + mu[i];
	for (int i = 1; i <= 50000; ++i)
	{
		for (int l = 1, r; l <= i; l = r + 1)
		{
			r = Min(i, i / (i / l));
			g[i] += 1ll * (r - l + 1) * (i / l);
		}
	}
}

int main()
{
	t = Read(); init();
	while (t--)
	{
		n = Read(), m = Read(); if (n > m) std::swap(n, m); LL ans = 0;
		for (int l1 = 1, r1; l1 <= n; l1 = r1 + 1)
		{
			r1 = Min(n, Min(n / (n / l1), m / (m / l1)));
			ans += 1ll * (mu[r1] - mu[l1 - 1]) * g[n / l1] * g[m / l1];
		}
		printf("%lld\n", ans);
	}
	return 0;
}