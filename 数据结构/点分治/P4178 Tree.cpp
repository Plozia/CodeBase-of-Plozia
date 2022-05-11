/*
========= Plozia =========
	Author:Plozia
	Problem:P4178 Tree
	Date:2021/6/18
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 4e4 + 5, MAXK = 2e4 + 5;
int n, Head[MAXN], cnt_Edge = 1, Node_cnt, Size[MAXN], dis[MAXN], q, Maxn[MAXN], Root, tmp[40000005], cnt_tmp;
struct node {int to, val, Next; } Edge[MAXN << 1];
bool vis[MAXN];
LL ans;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

namespace Segment_Tree
{
	struct Tree
	{
		int l, r, tag, sum;
		#define l(p) tree[p].l
		#define r(p) tree[p].r
		#define t(p) tree[p].tag
		#define s(p) tree[p].sum
	}tree[MAXK << 2];
	void build(int p, int l, int r)
	{
		l(p) = l, r(p) = r;
		if (l == r) { s(p) = t(p) = 0; return ; }
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		s(p) = t(p) = 0;
	}
	void spread(int p)
	{
		if (t(p))
		{
			s(p << 1) = s(p << 1 | 1) = 0;
			t(p << 1) = t(p << 1 | 1) = 1;
			t(p) = 0;
		}
	}
	void Change(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) { s(p) = 0, t(p) = 1; return ; }
		spread(p); int mid = (l(p) + r(p)) >> 1;
		if (l <= mid) Change(p << 1, l, r);
		if (r > mid) Change(p << 1 | 1, l, r);
		s(p) = s(p << 1) + s(p << 1 | 1);
	}
	void Add(int p, int x)
	{
		if (l(p) == r(p) && l(p) == x) { ++s(p); return ; }
		spread(p); int mid = (l(p) + r(p)) >> 1;
		if (x <= mid) Add(p << 1, x);
		else Add(p << 1 | 1, x);
		s(p) = s(p << 1) + s(p << 1 | 1);
	}
	LL Ask(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return s(p);
		spread(p); int mid = (l(p) + r(p)) >> 1; LL val = 0;
		if (l <= mid) val += Ask(p << 1, l, r);
		if (r > mid) val += Ask(p << 1 | 1, l, r);
		return val;
	}
}//线段树

using namespace Segment_Tree;

void Get_Root(int now, int father)
{
	Size[now] = 1, Maxn[now] = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		Get_Root(u, now); Size[now] += Size[u]; Maxn[now] = Max(Maxn[now], Size[u]);
	}
	Maxn[now] = Max(Maxn[now], Node_cnt - Maxn[now] - 1);
	if (Maxn[now] < Maxn[Root]) Root = now;
}//树的重心

void Get_Dis(int now, int father)
{
	if (dis[now] <= q) { ++cnt_tmp; tmp[cnt_tmp] = dis[now]; }
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father || vis[u]) continue ;
		dis[u] = dis[now] + Edge[i].val;
		Get_Dis(u, now);
	}
}

void Solve(int now)
{
	Add(1, 0);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		cnt_tmp = 0; dis[u] = Edge[i].val; Get_Dis(u, now);
		for (int j = 1; j <= cnt_tmp; ++j)
		{
			if (q >= tmp[j]) ans += (LL)Ask(1, 0, q - tmp[j]);
		}
		for (int j = 1; j <= cnt_tmp; ++j) Add(1, tmp[j]);
	}
	Change(1, 0, q);
}//计算贡献

void Divide(int now)
{
	vis[now] = 1; Solve(now);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		Maxn[Root = 0] = Node_cnt = Size[u];
		Get_Root(u, 0); Get_Root(Root, 0); Divide(Root);
	}
}//分治

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	q = Read();
	Maxn[Root = 0] = Node_cnt = n; build(1, 0, q);
	Get_Root(1, 0); Get_Root(Root, 0); Divide(Root);
	printf("%lld\n", ans); return 0;
}