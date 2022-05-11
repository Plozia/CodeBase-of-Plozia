/*
========= Plozia =========
	Author:Plozia
	Problem:P2515 [HAOI2010]软件安装
	Date:2021/7/18
	Remarks:Use Dev-C++ 5.9.2
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5, MAXM = 500 + 5;
int n, m, wold[MAXN], w[MAXN], vold[MAXN], v[MAXN], Color[MAXN], f[MAXN][MAXM], g[MAXM];
struct Graph
{
	int Head[MAXN] = {0}, cnt_Edge = 1;
	struct node { int to, val, Next; } Edge[MAXN << 1];
	void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }
}og, ng;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

namespace Work
{
	int sta[MAXN] = {0}, Top, col, cnt[MAXN] = {0};
	bool book[MAXN] = {0}, dis[MAXN][MAXN] = {0};
	void dfs1(int now)
	{
		book[now] = 1;
		for (int i = og.Head[now]; i; i = og.Edge[i].Next)
		{
			int u = og.Edge[i].to;
			if (book[u] || og.Edge[i].val == 1) continue ;
			dfs1(u);
		}
		sta[++Top] = now;
	}
	void dfs2(int now)
	{
		book[now] = 1, Color[now] = col;
		for (int i = og.Head[now]; i; i = og.Edge[i].Next)
		{
			int u = og.Edge[i].to;
			if (book[u] || og.Edge[i].val == 0) continue ;
			dfs2(u);
		}
	}
	void Main()
	{
		for (int i = 1; i <= n; ++i)
			if (!book[i]) dfs1(i);
		std::reverse(sta + 1, sta + Top + 1);
		memset(book, 0, sizeof(book));
		for (int i = 1; i <= n; ++i)
			if (!book[sta[i]]) { ++col; dfs2(sta[i]); }
		for (int i = 2; i <= og.cnt_Edge; i += 2)
		{
			int x = og.Edge[i].to, y = og.Edge[i ^ 1].to;
			if (Color[x] == Color[y]) continue ;
			dis[Color[y]][Color[x]] = 1;
		}
		for (int i = 1; i <= n; ++i) w[Color[i]] += wold[i], v[Color[i]] += vold[i];
		for (int i = 1; i <= col; ++i)
			for (int j = 1; j <= col; ++j)
				if (dis[i][j]) { ng.add_Edge(i, j, 0); ++cnt[j]; }
		for (int i = 1; i <= col; ++i)
			if (!cnt[i]) ng.add_Edge(0, i, 0);
	}
}

void TreeDP(int now, int father)
{
	for (int i = w[now]; i <= m; ++i) f[now][i] = v[now];
	for (int i = ng.Head[now]; i; i = ng.Edge[i].Next)
	{
		int u = ng.Edge[i].to; if (u == father) continue ; TreeDP(u, now);
		for (int j = 0; j <= m; ++j) g[j] = f[now][j];
		for (int j = 0; j <= m - w[now]; ++j)
			for (int k = 0; j + k <= m - w[now]; ++k)
				f[now][j + k + w[now]] = Max(f[now][j + k + w[now]], g[j + w[now]] + f[u][k]);
	}
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) wold[i] = Read();
	for (int i = 1; i <= n; ++i) vold[i] = Read();
	for (int i = 1; i <= n; ++i)
	{
		int x = Read();
		if (x != 0) { og.add_Edge(x, i, 0); og.add_Edge(i, x, 1); }
	}
	Work::Main(); TreeDP(0, -1); printf("%d\n", f[0][m]); return 0;
}