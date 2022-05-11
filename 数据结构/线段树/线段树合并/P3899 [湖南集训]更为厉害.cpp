/*
========= Plozia =========
	Author:Plozia
	Problem:P3899 [湖南集训]更为厉害
	Date:2022/3/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, q, Head[MAXN], cnt_Edge = 1, Size[MAXN], dep[MAXN], cntsgt, Root[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	int ls, rs; LL val;
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
void Update(int p) { val(p) = val(ls(p)) + val(rs(p)); }

void dfs1(int now, int father)
{
	dep[now] = dep[father] + 1; Size[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs1(u, now); Size[now] += Size[u];
	}
}

void Insert(int &p, int x, int val, int lp, int rp)
{
	if (!p) p = ++cntsgt;
	if (lp == rp) { val(p) += val; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Insert(ls(p), x, val, lp, mid);
	else Insert(rs(p), x, val, mid + 1, rp);
	Update(p);
}

int Merge(int p1, int p2, int lp, int rp)
{
	if (!p1 || !p2) return p1 | p2;
	int p = ++cntsgt; if (lp == rp) { val(p) = val(p1) + val(p2); return p; }
	int mid = (lp + rp) >> 1;
	ls(p) = Merge(ls(p1), ls(p2), lp, mid);
	rs(p) = Merge(rs(p1), rs(p2), mid + 1, rp);
	Update(p); return p;
}

void dfs2(int now, int father)
{
	Insert(Root[now], dep[now], Size[now] - 1, 1, n);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs2(u, now); Root[now] = Merge(Root[now], Root[u], 1, n);
	}
}

LL Query(int p, int l, int r, int lp, int rp)
{
	if (!p) return 0; if (lp >= l && rp <= r) return val(p);
	int mid = (lp + rp) >> 1; LL val = 0;
	if (l <= mid) val += Query(ls(p), l, r, lp, mid);
	if (r > mid) val += Query(rs(p), l, r, mid + 1, rp);
	return val;
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); add_Edge(x, y); add_Edge(y, x); }
	dfs1(1, 1); dfs2(1, 1);
	while (q--)
	{
		int p = Read(), k = Read(); LL ans = 0;
		ans = Query(Root[p], Min(dep[p] + 1, n), Min(n, dep[p] + k), 1, n);
		ans += 1ll * (Size[p] - 1) * Min(dep[p] - 1, k);
		printf("%lld\n", ans);
	}
	return 0;
}