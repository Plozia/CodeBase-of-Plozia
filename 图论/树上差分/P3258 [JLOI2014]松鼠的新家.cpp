/*
========= Plozia =========
	Author:Plozia
	Problem:P3258 [JLOI2014]松鼠的新家
	Date:2021/9/6
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, a[MAXN], Head[MAXN], cnt_Edge = 1, val[MAXN], dep[MAXN], fa[MAXN][20];
struct node { int To, Next; } Edge[MAXN << 1];

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
	fa[now][0] = father, dep[now] = dep[father] + 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs(u, now);
	}
}

void init()
{
	dfs(1, 0);
	for (int j = 1; j < 20; ++j)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 19; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void dfs2(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs2(u, now); val[now] += val[u];
	}
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	init();
	for (int i = 1; i < n; ++i)
	{
		int lca = LCA(a[i], a[i + 1]);
		++val[a[i]]; ++val[a[i + 1]]; --val[lca]; --val[fa[lca][0]];
	}
	dfs2(1, 1);
	for (int i = 2; i <= n; ++i) --val[a[i]];
	for (int i = 1; i <= n; ++i) printf("%d\n", val[i]);
	return 0;
}