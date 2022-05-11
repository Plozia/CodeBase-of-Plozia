/*
========= Plozia =========
	Author:Plozia
	Problem:P4180 [BJWC2010]严格次小生成树
	Date:2021/4/18
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10, MAXM = 3e5 + 10;
int n, m, Head[MAXM], cnt_Edge = 1, fa[MAXN];
LL ans, ans2, Plozia;
struct node1 { int to, Next; LL val; } Edge[MAXM << 1];
struct node2 { int x, y; LL z; int book; } a[MAXM];
int Fa[MAXN], Size[MAXN], Son[MAXN], Top[MAXN];
LL Old_val[MAXN], val[MAXN];
int id[MAXN], dep[MAXN], cnt;
struct node3
{
	int l, r;
	LL Maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define m(p) tree[p].Maxn
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y, LL z) { ++cnt_Edge; Edge[cnt_Edge] = (node1){y, Head[x], z}; Head[x] = cnt_Edge; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
bool cmp1(const node2 &fir, const node2 &sec) { return fir.z < sec.z; }

namespace Segment_Tree
{
	void build(int p, int l, int r)
	{
		l(p) = l, r(p) = r;
		if (l(p) == r(p)) { m(p) = val[l]; return ; }
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		m(p) = Max(m(p << 1), m(p << 1 | 1));
	}
	LL ask(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r)
		{
			if (m(p) != Plozia) return m(p);
		}
		if (l(p) == r(p)) return 0;
		int mid = (l(p) + r(p)) >> 1; LL ans = 0;
		if (l <= mid) ans = Max(ans, ask(p << 1, l, r));
		if (r > mid) ans = Max(ans, ask(p << 1 | 1, l, r));
		return ans;
	}
}

namespace Union
{
	void init() { for (int i = 1; i <= n; ++i) fa[i] = i; }
	int gf(int x) { return (fa[x] == x) ? x : fa[x] = gf(fa[x]); }
	void hb(int x, int y) { if (gf(x) != gf(y)) fa[fa[x]] = fa[y]; }
}

void dfs1(int now, int Father, int depth)
{
	Fa[now] = Father; Size[now] = 1; dep[now] = depth;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == Father) continue ;
		dfs1(u, now, depth + 1);
		Size[now] += Size[u];
		if (Size[u] > Size[Son[now]]) Son[now] = u;
	}
}

void dfs2(int now, int Top_father)
{
	Top[now] = Top_father; ++cnt; id[now] = cnt; val[cnt] = Old_val[now];
	if (!Son[now]) return ; dfs2(Son[now], Top_father);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == Fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

LL ask(int x, int y)
{
	LL sum = 0;
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		LL ans = Segment_Tree::ask(1, id[Top[x]], id[x]);
		sum = Max(ans, sum);
		x = Fa[Top[x]];
	}
	if (dep[x] < dep[y]) std::swap(x, y);
	if (x != y) sum = Max(sum, Segment_Tree::ask(1, id[y] + 1, id[x]));
	return sum;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) a[i].x = read(), a[i].y = read(), a[i].z = read();
	Union::init(); std::sort(a + 1, a + m + 1, cmp1);
	int ssum = n;
	for (int i = 1; i <= m; ++i)
	{
		if (Union::gf(a[i].x) == Union::gf(a[i].y)) continue;
		ans += a[i].z; Union::hb(a[i].x, a[i].y); --ssum; a[i].book = 1;
		add_Edge(a[i].x, a[i].y, a[i].z); add_Edge(a[i].y, a[i].x, a[i].z);
		if (ssum == 1) break;
	}
	dfs1(1, 1, 1);
	for (int i = 1; i <= m; ++i)
	{
		if (!a[i].book) continue ;
		int x = a[i].x, y = a[i].y;
		if (dep[x] < dep[y]) std::swap(x, y);
		Old_val[x] = a[i].z;
	}
	dfs2(1, 1); Segment_Tree::build(1, 1, n);
	ans2 = 0x7f7f7f7f7f7f7f7f;
	for (int i = 1; i <= m; ++i)
	{
		if (a[i].book == 1) continue ;
		Plozia = a[i].z;
		LL sum = ask(a[i].x, a[i].y);
		if (ans - sum + a[i].z > ans) ans2 = Min(ans2, ans - sum + a[i].z);
	}
	printf ("%lld\n", ans2); return 0;
}