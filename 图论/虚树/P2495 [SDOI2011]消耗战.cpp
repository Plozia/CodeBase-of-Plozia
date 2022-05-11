/*
========= Plozia =========
	Author:Plozia
	Problem:P2495 [SDOI2011]消耗战
	Date:2021/12/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2.5e5 + 5;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, q, fa[MAXN][21], dep[MAXN], dfn[MAXN], ask[MAXN << 1], book[MAXN];
LL f[MAXN], g[MAXN][21];
struct Graph
{
	int cnt_Edge = 1, Head[MAXN];
	struct node { int To, val, Next; } Edge[MAXN << 1];
	void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }
}og, ng;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

void dfs(int now, int father)
{
	dep[now] = dep[father] + 1; fa[now][0] = father; dfn[now] = ++dfn[0];
	for (int i = og.Head[now]; i; i = og.Edge[i].Next)
	{
		int u = og.Edge[i].To;
		if (u == father) continue ;
		g[u][0] = og.Edge[i].val; dfs(u, now);
	}
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
		{
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			g[i][j] = Min(g[i][j - 1], g[fa[i][j - 1]][j - 1]);
		}
}

int LCA_node(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

LL LCA_dis(int x, int y)
{
	LL val = INF;
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) { val = Min(val, g[x][i]); x = fa[x][i]; }
	if (x == y) return val;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) { val = Min(val, Min(g[x][i], g[y][i])); x = fa[x][i], y = fa[y][i]; }
	return Min(val, Min(g[x][0], g[y][0]));
}

bool cmp(const int &fir, const int &sec) { return dfn[fir] < dfn[sec]; }

void DP(int now, int father)
{
	for (int i = ng.Head[now]; i; i = ng.Edge[i].Next)
	{
		int u = ng.Edge[i].To;
		if (u == father) continue ;
		DP(u, now);
	}
	for (int i = ng.Head[now]; i; i = ng.Edge[i].Next)
	{
		int u = ng.Edge[i].To;
		if (u == father) continue ;
		if (book[u]) f[now] += LCA_dis(u, now);
		else f[now] += Min(f[u], LCA_dis(u, now));
	}
}

void Solve()
{
	int k = Read(); ask[1] = 1; ++k;
	for (int i = 2; i <= k; ++i) book[ask[i] = Read()] = 1;
	std::sort(ask + 1, ask + k + 1, cmp); ask[0] = k;
	for (int i = 2; i <= ask[0]; ++i)
	{
		int l = LCA_node(ask[i - 1], ask[i]);
		if (l != ask[i - 1] && l != ask[i]) ask[++k] = l;
	}
	std::sort(ask + 1, ask + k + 1);
	k = std::unique(ask + 1, ask + k + 1) - (ask + 1);
	std::sort(ask + 1, ask + k + 1, cmp);
	for (int i = 2; i <= k; ++i)
	{
		int l = LCA_node(ask[i - 1], ask[i]);
		ng.add_Edge(l, ask[i], 0);
	}
	DP(ask[1], ask[1]); printf("%lld\n", f[ask[1]]); ng.cnt_Edge = 1;
	for (int i = 1; i <= k; ++i) ng.Head[ask[i]] = f[ask[i]] = book[ask[i]] = 0;
}

int main()
{
	n = Read(); memset(g, 0x3f, sizeof(g));
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		og.add_Edge(x, y, z); og.add_Edge(y, x, z);
	}
	dfs(1, 1); init(); q = Read();
	for (int i = 1; i <= q; ++i) Solve();
	return 0;
}