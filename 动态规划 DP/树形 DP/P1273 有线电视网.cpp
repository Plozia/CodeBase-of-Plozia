/*
========= Plozia =========
	Author:Plozia
	Problem:P1273 有线电视网
	Date:2021/5/25
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3000 + 10;
int n, m, a[MAXN], Head[MAXN], cnt_Edge = 1, f[MAXN][MAXN], g[MAXN][MAXN], Size[MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	f[now][0] = 0; Size[now] = 1;
	if (now >= n - m + 1 && now <= n) { f[now][1] = a[now]; return ; }
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
		for (int j = 0; j <= m - 1; ++j) g[now][j] = f[now][j];
		for (int j = 0; j <= Size[u]; ++j)
			for (int k = 0; k <= Size[now]; ++k)
				f[now][j + k] = Max(f[now][j + k], f[u][j] - Edge[i].val + g[now][k]);
		Size[now] += Size[u];
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n - m; ++i)
	{
		int k = read();
		while (k--)
		{
			int y = read(), z = read();
			add_Edge(i, y, z); add_Edge(y, i, z);
		}
	}
	for (int i = n - m + 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m - 1; ++j)
			f[i][j] = -0x3f3f3f3f;
	dfs(1, 1);
	for (int i = m - 1; i >= 0; --i)
		if (f[1][i] >= 0) { printf("%d\n", i); return 0; }
	printf("0\n"); return 0;
}