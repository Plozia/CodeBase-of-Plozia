/*
========= Plozia =========
	Author:Plozia
	Problem:P3047 [USACO12FEB]Nearby Cows G
	Date:2021/5/25
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, k, Head[MAXN], cnt_Edge = 1, f[MAXN][30], a[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	f[now][0] = a[now];
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
		for (int j = 1; j <= k; ++j)
			f[now][j] += f[u][j - 1];
	}
}

void Change_Root(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		for (int j = k; j >= 2; --j) f[u][j] -= f[u][j - 2];
		for (int j = 1; j <= k; ++j) f[u][j] += f[now][j - 1];
		Change_Root(u, now);
	}
}

int main()
{
	n = read(), k = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		add_Edge(x, y); add_Edge(y, x);
	}
	for (int i = 1; i <= n; ++i) a[i] = read();
	dfs(1, 0); Change_Root(1, 0);
	for (int i = 1; i <= n; ++i)
	{
		int sum = 0;
		for (int j = 0; j <= k; ++j) sum += f[i][j];
		printf("%d\n", sum);
	}
	return 0;
}