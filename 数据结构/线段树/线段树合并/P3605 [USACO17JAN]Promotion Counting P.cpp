/*
========= Plozia =========
	Author:Plozia
	Problem:P3605 [USACO17JAN]Promotion Counting P
	Date:2021/12/9
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

using std::vector;

const int MAXN = 1e5 + 5;
int n, p[MAXN], d[MAXN], cntn, Head[MAXN], cnt_Edge = 1, cnt_SgT, Root[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];
struct SgT
{
	int l, r, sum;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
}tree[MAXN * 100];

void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void Insert(int &p, int x, int l, int r)
{
	if (!p) p = ++cnt_SgT;
	if (l == r) { ++s(p); return ; }
	int mid = (l + r) >> 1;
	if (x <= mid) Insert(l(p), x, l, mid);
	else Insert(r(p), x, mid + 1, r);
	s(p) = s(l(p)) + s(r(p));
}

int Merge(int p1, int p2, int l, int r)
{
	if (!p1 || !p2) return p1 + p2;
	int p = ++cnt_SgT;
	if (l == r) { s(p) = s(p1) + s(p2); return p; }
	int mid = (l + r) >> 1;
	l(p) = Merge(l(p1), l(p2), l, mid);
	r(p) = Merge(r(p1), r(p2), mid + 1, r);
	s(p) = s(l(p)) + s(r(p)); return p;
}

int Query(int p, int ql, int qr, int l, int r)
{
	if (ql > qr) return 0; if (!p) return 0;
	if (l >= ql && r <= qr) return s(p);
	int mid = (l + r) >> 1, val = 0;
	if (ql <= mid) val += Query(l(p), ql, qr, l, mid);
	if (qr > mid) val += Query(r(p), ql, qr, mid + 1, r);
	return val;
}

void dfs(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now); Root[now] = Merge(Root[now], Root[u], 1, MAXN - 5);
	}
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) d[i] = p[i] = Read();
	std::sort(d + 1, d + n + 1);
	cntn = std::unique(d + 1, d + n + 1) - (d + 1);
	for (int i = 1; i <= n; ++i) p[i] = std::lower_bound(d + 1, d + cntn + 1, p[i]) - d;
	for (int i = 1; i <= n; ++i) Insert(Root[i], p[i], 1, MAXN - 5);
	for (int i = 2; i <= n; ++i) { int x = Read(); add_Edge(x, i); }
	dfs(1, 1);
	for (int i = 1; i <= n; ++i) printf("%d\n", Query(Root[i], p[i] + 1, MAXN - 5, 1, MAXN - 5));
	return 0;
}