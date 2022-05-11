/*
========= Plozia =========
	Author:Plozia
	Problem:P3950 部落冲突
	Date:2022/4/24
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, q, Head[MAXN], cntEdge = 1, cntid, cntWar, Wars[MAXN];
int Top[MAXN], fa[MAXN], Size[MAXN], Son[MAXN], dep[MAXN], id[MAXN];
struct EDGE { int To, Next; } Edge[MAXN << 1];
struct SgT { int sum; } tree[MAXN << 2];
#define sum(p) tree[p].sum

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void addEdge(int x, int y) { ++cntEdge; Edge[cntEdge] = (EDGE){y, Head[x]}; Head[x] = cntEdge; }

void dfs1(int now, int father)
{
	fa[now] = father, Size[now] = 1, dep[now] = dep[father] + 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ; dfs1(u, now);
		Size[now] += Size[u]; if (Size[u] > Size[Son[now]]) Son[now] = u;
	}
}

void dfs2(int now, int Topfather)
{
	id[now] = ++cntid; Top[now] = Topfather;
	if (!Son[now]) return ; dfs2(Son[now], Topfather);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

void Change(int p, int x, int val, int lp, int rp)
{
	if (lp == rp) { sum(p) += val; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Change(p << 1, x, val, lp, mid);
	else Change(p << 1 | 1, x, val, mid + 1, rp);
	sum(p) = sum(p << 1) + sum(p << 1 | 1);
}

int Ask(int p, int l, int r, int lp, int rp)
{
	if (l > r) return 0; if (lp >= l && rp <= r) return sum(p);
	int mid = (lp + rp) >> 1, val = 0;
	if (l <= mid) val += Ask(p << 1, l, r, lp, mid);
	if (r > mid) val += Ask(p << 1 | 1, l, r, mid + 1, rp);
	return val;
}

int Query(int x, int y)
{
	int val = 0;
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		val += Ask(1, id[Top[x]], id[x], 1, n); x = fa[Top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	val += Ask(1, id[x] + 1, id[y], 1, n);
	return val;
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); addEdge(x, y); addEdge(y, x); }
	dfs1(1, 1); dfs2(1, 1);
	while (q--)
	{
		char ch = getchar(); while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
		if (ch == 'Q')
		{
			int x = Read(), y = Read();
			if (Query(x, y) == 0) puts("Yes");
			else puts("No");
		}
		else if (ch == 'C')
		{
			int x = Read(), y = Read(); if (dep[x] < dep[y]) std::swap(x, y);
			Change(1, id[x], 1, 1, n); ++cntWar; Wars[cntWar] = x;
		}
		else
		{
			int x = Read(); Change(1, id[Wars[x]], -1, 1, n);
		}
	}
	return 0;
}