/*
========= Plozia =========
	Author:Plozia
	Problem:P2590 [ZJOI2008]树的统计
	Date:2021/9/10
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e4 + 5;
int n, Head[MAXN], cnt_Edge = 1, Head[MAXN], Top[MAXN], dep[MAXN], fa[MAXN], id[MAXN], cnt, val[MAXN], a[MAXN], Size[MAXN], Son[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];
struct Sg
{
	int l, r, Maxn, sum;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define m(p) tree[p].Maxn
	#define s(p) tree[p].sum
}tree[MAXN << 2];

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

void dfs1(int now, int father)
{
	fa[now] = father, dep[now] = dep[father] + 1, Size[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to; if (u == father) continue ; dfs1(u, now);
		Size[now] += Size[u]; if (Size[Son[now]] < Size[u]) Son[now] = u;
	}
}

void dfs2(int now, int Top_father)
{
	Top[now] = Top_father, id[now] = ++cnt; val[cnt] = a[now];
	if (!Son[now]) return ;
	dfs2(Son[now], Top_father);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { m(p) = s(p) = val[l]; return ; }
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	m(p) = Max(m(p << 1), m(p << 1 | 1));
	s(p) = s(p << 1) + s(p << 1 | 1);
}

void Change(int p, int x, int d)
{
	if (l(p) == r(p) && l(p) == x) { m(p) = s(p) = d; return ; }
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) Change(p << 1, x, d);
	else Change(p << 1 | 1, x, d);
	s(p) = s(p << 1) + s(p << 1 | 1);
	m(p) = Maxn(m(p << 1), m(p << 1 | 1));
}

int Ask_Maxn(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return m(p);
	int mid = (l(p) + r(p)) >> 1, v = 0;
	if (l <= mid) v = Max(v, Ask_Maxn(p << 1, l, r));
	if (r > mid) v = Max(v, Ask_Maxn(p << 1 | 1, l, r));
	return v;
}

int Ask_Sum(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	int mid = (l(p) + r(p)) >> 1, v = 0;
	if (l <= mid) v += Ask_Sum(p << 1, l, r);
	if (r > mid) v += Ask_Sum(p << 1 | 1, l, r);
	return v;
}

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	for (int i = 1; i <= n; ++i) a[i] = Read();
	dfs1(1, 1); dfs2(1, 1); Build(1, 1, n);
}