/*
========= Plozia =========
	Author:Plozia
	Problem:P5556 圣剑护符
	Date:2021/7/1
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, aold[MAXN], a[MAXN], Head[MAXN], cnt_Edge = 1, Top[MAXN], Size[MAXN], Son[MAXN], id[MAXN], cnt, dep[MAXN], fa[MAXN], d[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];
struct Tree
{
	int l, r, sum, Tag;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define t(p) tree[p].Tag
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

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { s(p) = a[l]; t(p) = 0; return ; }
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) ^ s(p << 1 | 1);
}

void Spread(int p)
{
	if (t(p))
	{
		s(p << 1) ^= t(p); s(p << 1 | 1) ^= t(p);
		t(p << 1) ^= t(p); t(p << 1 | 1) ^= t(p); t(p) = 0;
	}
}

void Change(int p, int l, int r, int k)
{
	if (l(p) >= l && r(p) <= r) { s(p) ^= k; t(p) ^= k; return ; }
	Spread(p); int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) Change(p << 1, l, r, k);
	if (r > mid) Change(p << 1 | 1, l, r, k);
	s(p) = s(p << 1) ^ s(p << 1 | 1);
}

int Ask(int p, int x)
{
	if (l(p) == r(p) && l(p) == x) return s(p);
	Spread(p); int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) return Ask(p << 1, x);
	else return Ask(p << 1 | 1, x);
}

void dfs1(int now, int father, int depth)
{
	dep[now] = depth, fa[now] = father, Size[now] = 1;
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
	id[now] = ++cnt; a[cnt] = aold[now]; Top[now] = Top_father;
	if (Son[now] == 0) return ;
	dfs2(Son[now], Top_father);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

int Add(int x)
{
	for (int i = 33; i >= 0; --i)
	{
		if (x & (1 << i))
		{
			if (d[i] & x) x ^= d[i];
			else { d[i] = x; return 0; }
		}
	}
	return 1;
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) aold[i] = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	dfs1(1, 0, 1); dfs2(1, 1); Build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		string str;
		std::cin >> str;
		if (str == "Update")
		{
			int x = Read(), y = Read(), z = Read();
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				Change(1, id[Top[x]], id[x], z); x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			Change(1, id[x], id[y], z);
		}
		else
		{
			int x = Read(), y = Read();
			int dis = 0, lca = 0, tx = x, ty = y;
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				dis += id[x] - id[Top[x]]; x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			dis += id[y] - id[x]; lca = x;
			if (dis > 31) { printf("YES\n"); continue ; }
			for(int j = 0; j <= 33; ++j) d[j] = 0;
			bool flag = Add(Ask(1, id[lca]));
			for (int j = tx; j != lca; j = fa[j]) flag |= Add(Ask(1, id[j]));
			for (int j = ty; j != lca; j = fa[j]) flag |= Add(Ask(1, id[j]));
			if (flag) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}