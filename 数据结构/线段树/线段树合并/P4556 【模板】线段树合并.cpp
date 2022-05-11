/*
========= Plozia =========
	Author:Plozia
	Problem:P4556 【模板】线段树合并
	Date:2021/12/5
========= Plozia =========
*/

#include <bits/stdc++.h>

int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, Head[MAXN], cnt_Edge = 1, Root[MAXN], cnt_SgT, fa[MAXN][21], dep[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	int l, r, Maxn, ans;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define Maxn(p) tree[p].Maxn
	#define ans(p) tree[p].ans
}tree[MAXN * 100];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void Update(int p)
{
	if (Maxn(l(p)) >= Maxn(r(p))) { Maxn(p) = Maxn(l(p)); ans(p) = ans(l(p)); }
	else { Maxn(p) = Maxn(r(p)); ans(p) = ans(r(p)); }
}

void dfs(int now, int father)
{
	dep[now] = dep[father] + 1; fa[now][0] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs(u, now);
	}
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 0; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void Insert(int &p, int x, int k, int l, int r)
{
	if (!p) p = ++cnt_SgT;
	if (l == r && l == x) { Maxn(p) += k; ans(p) = x; return ; }
	int mid = (l + r) >> 1;
	if (x <= mid) Insert(l(p), x, k, l, mid);
	else Insert(r(p), x, k, mid + 1, r);
	Update(p);
}

int Merge(int p1, int p2, int l, int r)
{
	if (!p1 || !p2) { p1 = p1 + p2; return p1; }
	int p = ++cnt_SgT;
	if (l == r) { Maxn(p) = Maxn(p1) + Maxn(p2); ans(p) = l; return p; }
	int mid = (l + r) >> 1;
	l(p) = Merge(l(p1), l(p2), l, mid);
	r(p) = Merge(r(p1), r(p2), mid + 1, r);
	Update(p); return p;
}

void dfs2(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs2(u, now); Root[now] = Merge(Root[now], Root[u], 1, MAXN - 5);
	}
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	add_Edge(0, 1); add_Edge(1, 0);
	dfs(0, 0); init();
	for (int i = 1; i <= q; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		int l = LCA(x, y);
		Insert(Root[fa[l][0]], z, -1, 1, MAXN - 5);
		Insert(Root[l], z, -1, 1, MAXN - 5);
		Insert(Root[x], z, 1, 1, MAXN - 5);
		Insert(Root[y], z, 1, 1, MAXN - 5);
	}
	dfs2(0, 0);
	for (int i = 1; i <= n; ++i)
	{
		if (Maxn(Root[i]) == 0) printf("0\n");
		else printf("%d\n", ans(Root[i]));
	}
	return 0;
}