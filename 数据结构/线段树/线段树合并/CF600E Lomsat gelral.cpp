/*
========= Plozia =========
	Author:Plozia
	Problem:CF600E Lomsat gelral
	Date:2021/12/9
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, a[MAXN], cnt_Edge = 1, Head[MAXN], cnt_SgT, Root[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	int l, r, Maxn; LL ans;
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
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void Update(int p)
{
	if (Maxn(l(p)) > Maxn(r(p))) Maxn(p) = Maxn(l(p)), ans(p) = ans(l(p));
	else if (Maxn(l(p)) < Maxn(r(p))) Maxn(p) = Maxn(r(p)), ans(p) = ans(r(p));
	else Maxn(p) = Maxn(l(p)), ans(p) = ans(l(p)) + ans(r(p));
}

void Insert(int &p, int x, int l, int r)
{
	if (!p) p = ++cnt_SgT;
	if (l == r) { ++Maxn(p); ans(p) = x; return ; }
	int mid = (l + r) >> 1;
	if (x <= mid) Insert(l(p), x, l, mid);
	else Insert(r(p), x, mid + 1, r);
	Update(p);
}

int Merge(int p1, int p2, int l, int r)
{
	if (!p1 || !p2) return p1 + p2;
	int p = ++cnt_SgT;
	if (l == r) { Maxn(p) = Maxn(p1) + Maxn(p2); ans(p) = l; return p; }
	int mid = (l + r) >> 1;
	l(p) = Merge(l(p1), l(p2), l, mid);
	r(p) = Merge(r(p1), r(p2), mid + 1, r);
	Update(p); return p;
}

void dfs(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs(u, now); Root[now] = Merge(Root[now], Root[u], 1, n);
	}
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); add_Edge(x, y); add_Edge(y, x); }
	for (int i = 1; i <= n; ++i) Insert(Root[i], a[i], 1, n);
	dfs(1, 1);
	for (int i = 1; i <= n; ++i) printf("%lld%c", ans(Root[i]), " \n"[i == n]);
	return 0;
}