/*
========= Plozia =========
	Author:Plozia
	Problem:P3627 [APIO2009]抢掠计划
	Date:2021/4/15
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 5e5 + 10;
int n, m, Color[MAXN], col, cnt[MAXN], Start, Sta[MAXN], Top;
bool vis[MAXN];
LL ans, f[MAXN];
struct node1
{
	int Head[MAXN], cnt_Edge = 1; LL a[MAXN];
	struct node { int to, val, Next; } Edge[MAXN << 1];
	void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }
	int Wine[MAXN];
}Old_Graph, New_Graph;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

void dfs1(int now)
{
	vis[now] = 1;
	for (int i = Old_Graph.Head[now]; i; i = Old_Graph.Edge[i].Next)
	{
		int u = Old_Graph.Edge[i].to;
		if (vis[u] || Old_Graph.Edge[i].val == 0) continue;
		dfs1(u);
	}
	Sta[++Top] = now;
}

void dfs2(int now, int col)
{
	vis[now] = 1; Color[now] = col;
	for (int i = Old_Graph.Head[now]; i; i = Old_Graph.Edge[i].Next)
	{
		int u = Old_Graph.Edge[i].to;
		if (vis[u] || Old_Graph.Edge[i].val == 1) continue;
		dfs2(u, col);
	}
}

void Topsort()
{
	queue <int> q; memset(f, -0x3f, sizeof(f));
	for (int i = 1; i <= col; ++i)
		if (cnt[i] == 0) q.push(i);
	f[Color[Start]] = New_Graph.a[Color[Start]];
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = New_Graph.Head[x]; i; i = New_Graph.Edge[i].Next)
		{
			int u = New_Graph.Edge[i].to; --cnt[u];
			f[u] = Max(f[u], f[x] + New_Graph.a[u]);
			if (New_Graph.Wine[u]) ans = Max(ans, f[u]);
			if (cnt[u] == 0) q.push(u);
		}
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i)
	{
		int u = read(), v = read();
		Old_Graph.add_Edge(u, v, 1); Old_Graph.add_Edge(v, u, 0);
	}
	for (int i = 1; i <= n; ++i) Old_Graph.a[i] = read();
	Start = read(); int tmp = read();
	for (int i = 1; i <= tmp; ++i) Old_Graph.Wine[read()] = 1;
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i);
	memset(vis, 0, sizeof(vis)); std::reverse(Sta + 1, Sta + Top + 1);
	for (int i = 1; i <= n; ++i) if (!vis[Sta[i]]) { ++col; dfs2(Sta[i], col); }
	for (int i = 1; i <= Old_Graph.cnt_Edge; i += 2)
	{
		int u = Old_Graph.Edge[i].to, v = Old_Graph.Edge[i ^ 1].to;
		if (Color[u] != Color[v]) { ++cnt[Color[v]]; New_Graph.add_Edge(Color[u], Color[v], 1); }
	}
	for (int i = 1; i <= n; ++i) New_Graph.a[Color[i]] += Old_Graph.a[i];
	for (int i = 1; i <= n; ++i) New_Graph.Wine[Color[i]] |= Old_Graph.Wine[i];
	Topsort(); printf("%lld\n", ans);
	return 0;
}