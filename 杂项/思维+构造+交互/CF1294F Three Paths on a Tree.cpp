/*
========= Plozia =========
	Author:Plozia
	Problem:CF1294F Three Paths on a Tree
	Date:2021/6/30
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, dep[MAXN], u, v, w, Head[MAXN], cnt_Edge = 1, f[MAXN], Root = 0, ans, fa[MAXN];
int Path[MAXN], cnt;
bool book[MAXN];
struct node { int to, Next; } Edge[MAXN * 2 + 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father, int Tag)
{
	if (f[now] > ans) { Root = now; ans = f[now]; }
	if (Tag) fa[now] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		f[u] = f[now] + 1;
		dfs(u, now, Tag);
	}
}

void dfs2(int now, int father, int depth)
{
	dep[now] = depth;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father || book[u]) continue ;
		dfs2(u, now, depth + 1);
	}
}

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	f[Root = 1] = 0; dfs(1, 0, 0); ans = 0; u = Root;
	f[Root] = 0; dfs(Root, 0, 1); v = Root;
	for (int i = v; i != u; i = fa[i]) book[i] = 1, dep[i] = -1;
	book[u] = 1, dep[u] = -1;
	for (int i = fa[v]; i != u; i = fa[i]) { dep[i] = 0; dfs2(i, 0, 0); }
	int t = -1;
	for (int i = 1; i <= n; ++i)
		if (dep[i] > t) { t = dep[i]; w = i; }
	printf("%d\n%d %d %d\n", ans + t, u, v, w); return 0;
}