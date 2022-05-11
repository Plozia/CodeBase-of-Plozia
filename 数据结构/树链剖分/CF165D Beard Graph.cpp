/*
========= Plozia =========
	Author:Plozia
	Problem:CF165D Beard Graph
	Date:2021/8/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5, MAXM = 3e5 + 5;
int n, m, Head[MAXN], CntEdge = 1, a[MAXN], Fa[MAXN], Id[MAXN], Top[MAXN], Dep[MAXN], Size[MAXN], Son[MAXN], CntId;
struct node { int To, Next; } Edge[MAXN << 1];
struct EdgeNode { int x, y; } e[MAXN];
struct TreeNode
{
	int l, r, s;
	#define l(p) Tree[p].l
	#define r(p) Tree[p].r
	#define s(p) Tree[p].s
} Tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void AddEdge(int x, int y) { ++CntEdge; Edge[CntEdge] = (node){y, Head[x]}; Head[x] = CntEdge; }

void Dfs1(int now, int father)
{
	Fa[now] = father, Dep[now] = Dep[father] + 1, Size[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		Dfs1(u, now); Size[now] += Size[u]; if (Size[u] > Size[Son[now]]) Son[now] = u;
	}
}

void Dfs2(int now, int TopFather)
{
	Id[now] = ++CntId; Top[now] = TopFather; a[now] = 1;
	if (!Son[now]) return ;
	Dfs2(Son[now], TopFather);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == Fa[now] || u == Son[now]) continue ;
		Dfs2(u, u);
	}
}

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { s(p) = a[l]; return ; }
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
}

void Change(int p, int x, int d)
{
	if (l(p) == r(p) && l(p) == x) { s(p) = d; return ; }
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) Change(p << 1, x, d);
	else Change(p << 1 | 1, x, d);
	s(p) = s(p << 1) + s(p << 1 | 1);
}

int Ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	int mid = (l(p) + r(p)) >> 1, val = 0;
	if (l <= mid) val += Ask(p << 1, l, r);
	if (r > mid) val += Ask(p << 1 | 1, l, r);
	return val;
}

int GetLca(int x, int y)
{
	while (Top[x] != Top[y])
	{
		if (Dep[Top[x]] < Dep[Top[y]]) std::swap(x, y);
		x = Fa[Top[x]];
	}
	if (Dep[x] < Dep[y]) return x;
	return y;
}

int GetDis(int x, int y)
{
	int val = 0;
	while (Top[x] != Top[y])
	{
		if (Dep[Top[x]] < Dep[Top[y]]) std::swap(x, y);
		val += Ask(1, Id[Top[x]], Id[x]); x = Fa[Top[x]];
	}
	if (Dep[x] > Dep[y]) std::swap(x, y);
	if (x != y) val += Ask(1, Id[x] + 1, Id[y]);
	return val;
}

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(); e[i].x = x, e[i].y = y;
		AddEdge(x, y); AddEdge(y, x);
	}
	Dfs1(1, 1);	Dfs2(1, 1); Build(1, 1, n);
	m = Read();
	for (int i = 1; i <= m; ++i)
	{
		int op = Read();
		if (op == 1)
		{
			int u = Read();
			if (Dep[e[u].x] > Dep[e[u].y]) Change(1, Id[e[u].x], 1);
			else Change(1, Id[e[u].y], 1);
		}
		if (op == 2)
		{
			int u = Read();
			if (Dep[e[u].x] > Dep[e[u].y]) Change(1, Id[e[u].x], 0);
			else Change(1, Id[e[u].y], 0);
		}
		if (op == 3)
		{
			int x = Read(), y = Read();
			int Lca = GetLca(x, y), Dis = GetDis(x, y);
			if (Dep[x] + Dep[y] - 2 * Dep[Lca] == Dis) printf("%d\n", Dis);
			else printf("-1\n");
		}
	}
	return 0;
}