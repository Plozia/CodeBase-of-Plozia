/*
========= Plozia =========
	Author:Plozia
	Problem:P2341 [USACO03FALL][HAOI2006]受欢迎的牛 G
	Date:2021/4/20
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e4 + 10, MAXM = 5e4 + 10;
int n, m, cnt[MAXN], sta[MAXN], Top = 0, Col[MAXN], c, Size[MAXN];
bool vis[MAXN];

struct Graph
{
	int Head[MAXN], cnt_Edge = 1;
	struct node { int to, Next, val; } Edge[MAXM << 1];
	void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x], z}; Head[x] = cnt_Edge; }
}od, nd;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void dfs1(int now)
{
	vis[now] = 1;
	for (int i = od.Head[now]; i; i = od.Edge[i].Next)
	{
		int u = od.Edge[i].to;
		if (vis[u] || od.Edge[i].val == 0) continue ;
		dfs1(u);
	}
	sta[++Top] = now;
}

void dfs2(int now, int Color)
{
	vis[now] = 1; Col[now] = Color;
	for (int i = od.Head[now]; i; i = od.Edge[i].Next)
	{
		int u = od.Edge[i].to;
		if (vis[u] || od.Edge[i].val == 1) continue ;
		dfs2(u, Color);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		od.add_Edge(x, y, 1); od.add_Edge(y, x, 0);
	}
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i);
	memset(vis, 0, sizeof(vis)); std::reverse(sta + 1, sta + Top + 1);
	for (int i = 1; i <= n; ++i) if (!vis[sta[i]]) { ++c; dfs2(sta[i], c); }
	for (int i = 2; i <= od.cnt_Edge; i += 2)
	{
		int u = od.Edge[i ^ 1].to, v = od.Edge[i].to;
		if (Col[u] != Col[v]) { nd.add_Edge(Col[u], Col[v], 1); ++cnt[Col[u]]; }
	}
	for (int i = 1; i <= n; ++i) ++Size[Col[i]];
	int ans = 0, sum = 0;
	for (int i = 1; i <= c; ++i)
		if (cnt[i] == 0) { ++sum; ans = Size[i]; }
	if (sum > 1) printf("0\n");
	else printf("%d\n", ans);
	return 0;
}