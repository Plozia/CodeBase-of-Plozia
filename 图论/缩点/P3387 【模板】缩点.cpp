/*
========= Plozia =========
	Author:Plozia
	Problem:P3387 【模板】缩点
	Date:2021/4/15
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 1e4 + 10, MAXM = 1e5 + 10;
int n, m, val[MAXN], cnt_EEdge = 1, a[MAXN], HHead[MAXN], cnt_Edge = 1, sta[MAXN], Top, col, Color[MAXN], Head[MAXN];
int cnt[MAXN], ans, f[MAXN];
struct node { int to, val, Next; } EEdge[MAXM << 1], Edge[MAXM << 1];
bool vis[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_EEdge(int x, int y, int z) { ++cnt_EEdge; EEdge[cnt_EEdge] = (node){y, z, HHead[x]}; HHead[x] = cnt_EEdge; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }
//千万注意不能搞错原图和新图的存储！！！
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

void dfs1(int now)
{
	vis[now] = 1;
	for (int i = HHead[now]; i; i = EEdge[i].Next)
	{
		int u = EEdge[i].to;
		if (EEdge[i].val == 0) continue;
		if (vis[u]) continue; dfs1(u);
	}
	sta[++Top] = now;//进栈
}

void dfs2(int now, int col)
{
	vis[now] = 1; Color[now] = col;//染色，记录是哪一个强连通分量
	for (int i = HHead[now]; i; i = EEdge[i].Next)
	{
		int u = EEdge[i].to;
		if (vis[u] || EEdge[i].val == 1) continue;
		dfs2(u, col);
	}
}

void Topsort()//拓扑排序 + DP
{
	queue <int> q;
	for (int i = 1; i <= col; ++i)
		if (cnt[i] == 0) q.push(i), ans = Max(ans, f[i] = a[i]);
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to; --cnt[u];
			f[u] = Max(f[u], f[x] + a[u]);
			ans = Max(ans, f[u]);
			if (cnt[u] == 0) q.push(u);
		}
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 1; i <= m; ++i)
	{
		int u = read(), v = read();
		add_EEdge(u, v, 1); add_EEdge(v, u, 0);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs1(i);//一次 dfs
	memset(vis, 0, sizeof(vis));
	std::reverse(sta + 1, sta + Top + 1);//注意反转！
	for (int i = 1; i <= n; ++i)
		if (!vis[sta[i]]) { ++col; dfs2(sta[i], col); }//二次 dfs
	for (int i = 1; i <= cnt_EEdge; i += 2)
	{
		int u = EEdge[i ^ 1].to, v = EEdge[i].to;
		if (Color[u] != Color[v]) { add_Edge(Color[u], Color[v], 1); cnt[Color[v]]++; }
		//建立新图
	}
	for (int i = 1; i <= n; ++i) a[Color[i]] += val[i];//处理新图的点权
	Topsort(); printf("%d\n", ans);
	return 0;
}