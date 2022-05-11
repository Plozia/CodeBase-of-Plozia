/*
========= Plozia =========
	Author:Plozia
	Problem:CF613D Kingdom and its Cities
	Date:2021/11/29
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, sta[MAXN], Top, ask[MAXN << 1], fa[MAXN][21], dep[MAXN], Size[MAXN], dfn[MAXN], ans;
struct Graph
{
	int cnt_Edge = 1, Head[MAXN];
	struct node { int to, Next; } Edge[MAXN << 1];
	void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }
}og, ng;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp(const int &fir, const int &sec) { return dfn[fir] < dfn[sec]; }

void dfs(int now, int father)
{
	fa[now][0] = father; dep[now] = dep[father] + 1; ++dfn[0]; dfn[now] = dfn[0];
	for (int i = og.Head[now]; i; i = og.Edge[i].Next)
	{
		int u = og.Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
	}
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void Calc(int now)
{
	if (Size[now])
	{
		for (int i = ng.Head[now]; i; i = ng.Edge[i].Next)
		{
			int u = ng.Edge[i].to; Calc(u);
			if (Size[u]) { Size[u] = 0; ++ans;}
		}
	}
	else
	{
		int sum = 0;
		for (int i = ng.Head[now]; i; i = ng.Edge[i].Next)
		{
			int u = ng.Edge[i].to; Calc(u);
			if (Size[u]) ++sum; Size[u] = 0;
		}
		if (sum == 1) Size[now] = 1;
		else if (sum > 1) ++ans;
	}
	ng.Head[now] = 0;
}

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		og.add_Edge(x, y); og.add_Edge(y, x);
	}
	dfs(1, 1); init(); q = Read();
	for (int i = 1; i <= q; ++i)
	{
		int k = Read(); ans = 0;
		for (int j = 1; j <= k; ++j) Size[ask[j] = Read()] = 1;
		bool flag = 0;
		for (int j = 1; j <= k; ++j)
			if (ask[j] != 1 && Size[fa[ask[j]][0]]) flag = 1;
		if (flag)
		{
			for (int j = 1; j <= k; ++j) Size[ask[j]] = 0;
			puts("-1"); continue ;
		}
		std::sort(ask + 1, ask + k + 1, cmp); ask[0] = k;
		for (int j = 2; j <= k; ++j)
		{
			int l = LCA(ask[j - 1], ask[j]);
			if (l != ask[j - 1] && l != ask[j]) ask[++ask[0]] = l;
		}
		k = ask[0]; std::sort(ask + 1, ask + k + 1);
		k = std::unique(ask + 1, ask + k + 1) - (ask + 1);
		std::sort(ask + 1, ask + k + 1, cmp);
		for (int j = 2; j <= k; ++j)
		{
			int l = LCA(ask[j - 1], ask[j]);
			ng.add_Edge(l, ask[j]);
		}
		Calc(ask[1]); ng.cnt_Edge = 1; printf("%d\n", ans);
		for (int j = 1; j <= k; ++j) Size[ask[j]] = 0;
	}
	return 0;
}