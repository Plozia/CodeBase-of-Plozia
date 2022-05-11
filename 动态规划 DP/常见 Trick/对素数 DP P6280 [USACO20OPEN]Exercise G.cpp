/*
========= Plozia =========
	Author:Plozia
	Problem:P6280 [USACO20OPEN]Exercise G
	Date:2021/11/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e4 + 5;
int n, m, f[MAXN], Prime[MAXN];
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

int main()
{
	n = Read(), m = Read();
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) Prime[++Prime[0]] = i;
		for (int j = 1; j <= Prime[0]; ++j)
		{
			if (i * Prime[j] > n) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break ;
		}
	}
	f[0] = 1;
	for (int i = 1; i <= Prime[0]; ++i)
	{
		for (int j = n; j >= 0; --j)
		{
			LL tmp = Prime[i];
			while (j - tmp >= 0) { f[j] = (f[j] + 1ll * tmp * f[j - tmp]) % m; tmp = tmp * Prime[i]; }
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; ++i) ((ans += f[i]) >= m) ? (ans -= m) : 0;
	printf("%d\n", ans); return 0;
}