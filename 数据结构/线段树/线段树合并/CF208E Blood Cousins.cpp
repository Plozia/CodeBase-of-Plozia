/*
========= Plozia =========
	Author:Plozia
	Problem:CF208E Blood Cousins
	Date:2022/3/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, Head[MAXN], cnt_Edge = 1, fa[MAXN][20], dep[MAXN], Root[MAXN], cntsgt;
bool vis[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	int ls, rs, val;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
	#define val(p) tree[p].val
}tree[MAXN * 100];

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

void dfs1(int now, int father)
{
	dep[now] = dep[father] + 1; fa[now][0] = father; vis[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ; dfs1(u, now);
	}
}

void Insert(int &p, int val, int l, int r)
{
	if (!p) p = ++cntsgt;
	if (l == r) { ++val(p); return ; }
	int mid = (l + r) >> 1;
	if (val <= mid) Insert(ls(p), val, l, mid);
	else Insert(rs(p), val, mid + 1, r);
}

int Merge(int p1, int p2, int l, int r)
{
	if (!p1 || !p2) { p1 = p1 + p2; return p1; }
	int p = ++cntsgt; if (l == r) { val(p) = val(p1) + val(p2); return p; }
	int mid = (l + r) >> 1;
	ls(p) = Merge(ls(p1), ls(p2), l, mid);
	rs(p) = Merge(rs(p1), rs(p2), mid + 1, r);
	return p;
}

void dfs2(int now, int father)
{
	Insert(Root[now], dep[now], 1, n); vis[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs2(u, now); Root[now] = Merge(Root[now], Root[u], 1, n);
	}
}

int Ask(int x, int v)
{
	for (int j = 19; j >= 0; --j)
		if (v & (1 << j)) x = fa[x][j];
	return x;
}

int Query(int p, int x, int l, int r)
{
	if (!p) return 0; if (l == r) return val(p);
	int mid = (l + r) >> 1;
	if (x <= mid) return Query(ls(p), x, l, mid);
	else return Query(rs(p), x, mid + 1, r);
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
	{
		int x = Read(); if (x == 0) continue ;
		add_Edge(x, i); add_Edge(i, x);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs1(i, i);
	for (int j = 1; j <= 19; ++j)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for (int i = 1; i <= n; ++i) vis[i] = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs2(i, i);
	q = Read();
	for (int _ = 1; _ <= q; ++_)
	{
		int x = Read(), v = Read(), f = Ask(x, v);
		if (dep[f] + v != dep[x]) { printf("0 "); continue ; }
		printf("%d ", Query(Root[f], dep[x], 1, n) - 1);
	}
	puts(""); return 0;
}