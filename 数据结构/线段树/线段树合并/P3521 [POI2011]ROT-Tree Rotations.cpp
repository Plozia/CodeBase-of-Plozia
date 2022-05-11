/*
========= Plozia =========
	Author:Plozia
	Problem:P3521 [POI2011]ROT-Tree Rotations
	Date:2021/12/9
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 6e5 + 5;
int n, Head[MAXN], cnt_Edge = 1, Root[MAXN], r, cnt_SgT, cnt_Node;
LL ans, fir, sec;
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	int l, r; LL sum;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
}tree[7000005];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

int Read_Tree()
{
	int t = Read();
	if (t != 0) return t;
	else
	{
		t = ++cnt_Node;
		add_Edge(t, Read_Tree());
		add_Edge(t, Read_Tree());
		return t;
	}
}

void Insert(int &p, int x, int l, int r)
{
	if (!p) p = ++cnt_SgT;
	if (l == r) { ++s(p); return ; }
	int mid = (l + r) >> 1;
	if (x <= mid) Insert(l(p), x, l, mid);
	else Insert(r(p), x, mid + 1, r);
	s(p) = s(l(p)) + s(r(p)); return ;
}

int Merge(int p1, int p2, int l, int r)
{
	if (!p1 || !p2) return p1 + p2;
	int p = ++cnt_SgT;
	if (l == r) { s(p) = s(p1) + s(p2); return p; }
	int mid = (l + r) >> 1;
	fir = (fir + s(r(p1)) * s(l(p2)));
	sec = (sec + s(l(p1)) * s(r(p2)));
	l(p) = Merge(l(p1), l(p2), l, mid);
	r(p) = Merge(r(p1), r(p2), mid + 1, r);
	s(p) = s(l(p)) + s(r(p)); return p;
}

void dfs(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs(u, now); fir = sec = 0;
		Root[now] = Merge(Root[now], Root[u], 0, n);
		ans += Min(fir, sec);
	}
}

int main()
{
	cnt_Node = n = Read(); r = Read_Tree();
	if (n == 1) { puts("0"); return 0; }
	for (int i = 1; i <= n; ++i) Insert(Root[i], i, 0, n);
	dfs(r, r); printf("%lld\n", ans); return 0;
}