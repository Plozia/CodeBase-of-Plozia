/*
========= Plozia =========
	Author:Plozia
	Problem:CF995F Cowmpany Cowmpensation
	Date:2021/10/6
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3000 + 5;
const LL P = 1e9 + 7;
int n, Head[MAXN], cnt_Edge = 1;
LL d, f[MAXN][MAXN];
struct node { int to, Next; } Edge[MAXN << 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	f[now][1] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
		for (int j = 2; j <= n; ++j)
		{
			if (f[u][j] + f[u][j - 1] != 0) f[now][j] = (f[now][j] == 0) ? 1 : f[now][j];
			f[now][j] = f[now][j] * (f[u][j] + f[u][j - 1]) % P;
		}
	}
}

LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

int main()
{
	n = Read(); d = Read();
	for (int i = 2; i <= n; ++i)
	{
		int x = Read();
		add_Edge(i, x); add_Edge(x, i);
	}
	dfs(1, 1);
	LL fir = d, ans = 0;
	for (int i = 1; i <= Min(n, d); ++i)
	{
		ans = (ans + f[1][i] * fir % P) % P;
		fir = fir * (d - i) % P * ksm(i + 1) % P;
	}
	printf("%lld\n", ans); return 0;
}