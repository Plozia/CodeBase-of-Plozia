/*
========= Plozia =========
	Author:Plozia
	Problem:P4211 [LNOI2014]LCA
	Date:2021/6/24
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 50000 + 5, P = 201314;
int n, q, Head[MAXN], cnt_Edge = 1, cnt_que, Size[MAXN], dep[MAXN], Top[MAXN], fa[MAXN], id[MAXN], Son[MAXN], cnt;
struct node { int to, Next; } Edge[MAXN << 1];
struct query1
{
	int l, r, z, ans;
}a[MAXN];
struct query2
{
	int r, z, id, ans;
}d[MAXN << 1];
struct Segment_Tree
{
	int l, r, sum, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define a(p) tree[p].add
}tree[MAXN << 2];

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
bool cmp(const query2 &fir, const query2 &sec) { return fir.r < sec.r; }

void dfs1(int now, int father, int depth)
{
	Size[now] = 1, dep[now] = depth, fa[now] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs1(u, now, depth + 1);
		Size[now] += Size[u];
		if (Size[Son[now]] < Size[u]) Son[now] = u;
	}
}

void dfs2(int now, int Top_father)
{
	Top[now] = Top_father, id[now] = ++cnt;
	if (!Son[now]) return ;
	dfs2(Son[now], Top_father);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
}

void Spread(int p)
{
	if (a(p))
	{
		s(p << 1) = (s(p << 1) + 1ll * (r(p << 1) - l(p << 1) + 1) * a(p) % P) % P;
		s(p << 1 | 1) = (s(p << 1 | 1) + 1ll * (r(p << 1 | 1) - l(p << 1 | 1) + 1) * a(p) % P) % P;
		a(p << 1) = (a(p << 1) + a(p)) % P; a(p << 1 | 1) = (a(p << 1 | 1) + a(p)) % P; a(p) = 0;
	}
}

void Add(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r)
	{
		s(p) = (s(p) + (r(p) - l(p) + 1)) % P;
		++a(p); a(p) %= P; return ;
	}
	Spread(p); int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) Add(p << 1, l, r);
	if (r > mid) Add(p << 1 | 1, l, r);
	s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
}

int Ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	Spread(p); int mid = (l(p) + r(p)) >> 1, val = 0;
	if (l <= mid) val = (val + Ask(p << 1, l, r)) % P;
	if (r > mid) val = (val + Ask(p << 1 | 1, l, r)) % P;
	return val;
}

void Change(int x, int y)
{
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		Add(1, id[Top[x]], id[x]); x = fa[Top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	Add(1, id[x], id[y]);
}

int Query(int x, int y)
{
	int sum = 0;
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		sum = (sum + Ask(1, id[Top[x]], id[x])) % P; x = fa[Top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	sum = (sum + Ask(1, id[x], id[y])) % P; return sum;
}

int main()
{
	n = Read(), q = Read();
	for (int i = 2; i <= n; ++i)
	{
		int x = Read() + 1;
		add_Edge(i, x); add_Edge(x, i);
	}
	for (int i = 1; i <= q; ++i)
	{
		a[i].l = Read() + 1, a[i].r = Read() + 1, a[i].z = Read() + 1;
		d[++cnt_que] = (query2){a[i].l - 1, a[i].z, i, 0};
		d[++cnt_que] = (query2){a[i].r, a[i].z, i, 0};
	}
	std::sort(d + 1, d + cnt_que + 1, cmp);
	dfs1(1, 0, 0); dfs2(1, 1); Build(1, 1, n);
	int r = 1;
	for (int i = 1; i <= cnt_que; ++i)
	{
		for (; r <= d[i].r; ++r) Change(1, r);
		d[i].ans = Query(1, d[i].z);
	}
	for (int i = 1; i <= cnt_que; ++i)
	{
		if (d[i].r == a[d[i].id].l - 1)
		{
			a[d[i].id].ans -= d[i].ans;
		}
		else
		{
			a[d[i].id].ans += d[i].ans;
		}
	}
	for (int i = 1; i <= q; ++i) printf("%d\n", (a[i].ans % P + P) % P); return 0;
}