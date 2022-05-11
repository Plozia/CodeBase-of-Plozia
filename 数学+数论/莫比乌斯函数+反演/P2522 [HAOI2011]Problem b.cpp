/*
========= Plozia =========
	Author:Plozia
	Problem:P2522 [HAOI2011]Problem b
	Date:2022/2/20
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 5;
int t, a, b, c, d, k, mu[MAXN], Prime[MAXN];
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
	mu[1] = 1; book[1] = 1;
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
	for (int i = 1; i <= 50000; ++i) mu[i] = mu[i - 1] + mu[i];
}

LL Calc(int n, int m)
{
	LL ans = 0;
	for (int l = 1, r, tmp = Min(n, m); l <= tmp; l = r + 1)
	{
		r = Min(((n / l) ? (n / (n / l)) : tmp), Min(tmp, ((m / l) ? (m / (m / l)) : tmp)));
		ans += 1ll * (n / l) * (m / l) * (mu[r] - mu[l - 1]);
	}
	return ans;
}

int main()
{
	t = Read(); init();
	while (t--)
	{
		a = Read(), b = Read(), c = Read(), d = Read(), k = Read();
		printf("%lld\n", Calc(b / k, d / k) - Calc(b / k, (c - 1) / k) - Calc((a - 1) / k, d / k) + Calc((a - 1) / k, (c - 1) / k));
	}
	return 0;
}