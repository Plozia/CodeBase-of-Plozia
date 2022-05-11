/*
========= Plozia =========
	Author:Plozia
	Problem:P2605 [ZJOI2010]基站选址
	Date:2021/5/9
========= Plozia =========
*/

#include <bits/stdc++.h>
#define int long long

typedef long long LL;
const int MAXN = 20000 + 10, INF = 0x7f7f7f7f;
int n, k, dis[MAXN], Cost[MAXN], Range[MAXN], pay[MAXN], left[MAXN], right[MAXN], Head[MAXN], cnt_Edge = 1, f[MAXN], ans;
struct node { int to, Next; } Edge[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

struct Segment_tree
{
	struct Tree
	{
		int l, r, sum, add;
		#define l(p) tree[p].l
		#define r(p) tree[p].r
		#define s(p) tree[p].sum
		#define a(p) tree[p].add
	}tree[MAXN << 2];
	void build(int p, int l, int r)
	{
		l(p) = l, r(p) = r, a(p) = 0;
		if (l == r) { s(p) = f[l]; return ; }
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		s(p) = Min(s(p << 1), s(p << 1 | 1));
	}
	void spread(int p)
	{
		if (a(p))
		{
			s(p << 1) += a(p); s(p << 1 | 1) += a(p);
			a(p << 1) += a(p); a(p << 1 | 1) += a(p);
			a(p) = 0;
		}
	}
	void add(int p, int l, int r, int k)
	{
		if (l > r) return ;
		if (l(p) >= l && r(p) <= r) { s(p) += k; a(p) += k; return ; }
		spread(p); int mid = (l(p) + r(p)) >> 1;
		if (l <= mid) add(p << 1, l, r, k);
		if (r > mid) add(p << 1 | 1, l, r, k);
		s(p) = Min(s(p << 1), s(p << 1 | 1));
	}
	int ask(int p, int l, int r)
	{
		if (l > r) return INF;
		if (l(p) >= l && r(p) <= r) return s(p);
		spread(p); int mid = (l(p) + r(p)) >> 1, val = INF;
		if (l <= mid) val = Min(val, ask(p << 1, l, r));
		if (r > mid) val = Min(val, ask(p << 1 | 1, l, r));
		return val;
	}
}Seg;

void Init()
{
	int sum = 0;
	for(int i = 1; i <= n; ++i)
	{
		f[i] = sum + Cost[i];
		for (int j = Head[i]; j; j = Edge[j].Next) sum += pay[Edge[j].to];
	}
}

signed main()
{
	n = read(), k = read();
	for (int i = 2; i <= n; ++i) dis[i] = read();
	for (int i = 1; i <= n; ++i) Cost[i] = read();
	for (int i = 1; i <= n; ++i) Range[i] = read();
	for (int i = 1; i <= n; ++i) pay[i] = read();
	++n; ++k; dis[n] = pay[n] = INF;
	for (int i = 1; i <= n; ++i)
	{
		left[i] = std::lower_bound(dis + 1, dis + n + 1, dis[i] - Range[i]) - dis;
		right[i] = std::lower_bound(dis + 1, dis + n + 1, dis[i] + Range[i]) - dis;
		if (dis[right[i]] > dis[i] + Range[i]) --right[i];
		add_Edge(right[i], i);
	}
	Init(); ans = f[n];
	for (int i = 2; i <= k; ++i)
	{
		Seg.build(1, 1, n);
		for (int j = 1; j <= n; ++j)
		{
			f[j] = Seg.ask(1, 1, j - 1) + Cost[j];
			for (int k = Head[j]; k; k = Edge[k].Next) Seg.add(1, 1, left[Edge[k].to] - 1, pay[Edge[k].to]);
		}
		ans = Min(ans, f[n]);
	}
	printf("%lld\n", ans); return 0;
}