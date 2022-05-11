/*
========= Plozia =========
	Author:Plozia
	Problem:P1600 [NOIP2016 提高组] 天天爱跑步
	Date:2022/5/10
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, m, Head[MAXN], cntEdge, dep[MAXN], fa[MAXN][21], w[MAXN], Root[MAXN], ans[MAXN], cntSgT;
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT { int val, ls, rs; } tree[MAXN * 40]; // 是值域线段树……
#define val(p) tree[p].val
#define ls(p) tree[p].ls
#define rs(p) tree[p].rs

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void addEdge(int x, int y) { Edge[++cntEdge] = (node){y, Head[x]}; Head[x] = cntEdge; }

void dfs1(int now, int father)
{
	dep[now] = dep[father] + 1; fa[now][0] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ; dfs1(u, now);
	}
}
void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
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

void Insert(int &p, int x, int k, int lp, int rp)
{
	if (!p) p = ++cntSgT; if (x < lp || x > rp) return ;
	if (lp == rp) { val(p) += k; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Insert(ls(p), x, k, lp, mid);
	else Insert(rs(p), x, k, mid + 1, rp);
}
void Merge(int &p1, int p2, int lp, int rp)
{
	if (!p1 || !p2) { p1 = p1 + p2; return ; }
	if (lp == rp) { val(p1) += val(p2); return ; }
	int mid = (lp + rp) >> 1;
	Merge(ls(p1), ls(p2), lp, mid);
	Merge(rs(p1), rs(p2), mid + 1, rp);
}
int Ask(int p, int x, int lp, int rp)
{
	if (!p || x < lp || x > rp) return 0;
	if (lp == rp) return val(p);
	int mid = (lp + rp) >> 1;
	if (x <= mid) return Ask(ls(p), x, lp, mid);
	else return Ask(rs(p), x, mid + 1, rp);
}

void dfs2(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs2(u, now); Merge(Root[now], Root[u], -n, n);
	}
	ans[now] = Ask(Root[now], dep[now] + w[now], -n, n);
	if (w[now] != 0) ans[now] += Ask(Root[now], dep[now] - w[now], -n, n);
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); addEdge(x, y); addEdge(y, x); }
	dfs1(1, 0); init();
	for (int i = 1; i <= n; ++i) w[i] = Read();
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(), lca = LCA(x, y);
		Insert(Root[x], dep[x], 1, -n, n);
		Insert(Root[y], dep[y] - (dep[x] + dep[y] - 2 * dep[lca]), 1, -n, n);
		Insert(Root[lca], dep[x], -1, -n, n);
		Insert(Root[fa[lca][0]], dep[y] - (dep[x] + dep[y] - 2 * dep[lca]), -1, -n, n);
	}
	dfs2(1, 1);
	for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}