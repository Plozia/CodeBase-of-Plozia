/*
========= Plozia =========
	Author:Plozia
	Problem:P2396 yyy loves Maths VII
	Date:2021/6/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAX_State = (1 << 24) + 10, MAXN = 24 + 10, P = 1e9 + 7;
int n, m, b[3], f[MAX_State], dis[MAX_State];

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
	n = Read();
	for (int i = 1; i <= n; ++i) dis[1 << (i - 1)] = Read();
	m = Read(); b[1] = b[2] = -0x7f7f7f7f;
	for (int i = 1; i <= m; ++i) b[i] = Read();
	f[0] = 1;
	for (int i = 1; i <= (1 << n) - 1; ++i)
	{
		int l = i & (-i);
		dis[i] = dis[i - l] + dis[l];
		if (dis[i] == b[1] || dis[i] == b[2]) continue ;
		for (int j = i & (-i), k = i; k; k -= j, j = k & (-k))
			{ f[i] = (f[i] + f[i - j]) % P; }
	}
	printf("%lld\n", f[(1 << n) - 1]); return 0;
}