/*
========= Plozia =========
	Author:Plozia
	Problem:P2486 [SDOI2011]Ⱦɫ
	Date:2021/3/9
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, wfir[MAXN];
int Size[MAXN], Son[MAXN], dep[MAXN], fa[MAXN], Top[MAXN], id[MAXN], w[MAXN], cnt;
vector <int> Next[MAXN];
struct node
{
	int firnum, lasnum;
	int sum, l, r, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define a(p) tree[p].add
	#define fir(p) tree[p].firnum
	#define las(p) tree[p].lasnum
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -=  (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

namespace Segment_tree
{
	void build(int p, int l, int r)
	{
		l(p) = l, r(p) = r;
		if (l == r) {s(p) = 1; fir(p) = las(p) = w[l]; return ;}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		s(p) = s(p << 1) + s(p << 1 | 1);
		if (las(p << 1) == fir(p << 1 | 1)) --s(p);
		fir(p) = fir(p << 1), las(p) = las(p << 1 | 1);
	}
	
	void spread(int p)
	{
		if (a(p))
		{
			s(p << 1) = s(p << 1 | 1) = 1; 
			a(p << 1) = a(p << 1 | 1) = a(p);
			fir(p << 1) = fir(p << 1 | 1) = las(p << 1) = las(p << 1 | 1) = a(p);
			a(p) = 0;
		}
	}
	
	void change(int p, int l, int r, int c)
	{
		if (l(p) >= l && r(p) <= r) {s(p) = 1; a(p) = fir(p) = las(p) = c; return ;}
		spread(p);
		int mid = (l(p) + r(p)) >> 1;
		if (l <= mid) change(p << 1, l, r, c);
		if (r > mid) change(p << 1 | 1, l, r, c);
		s(p) = s(p << 1) + s(p << 1 | 1);
		if (las(p << 1) == fir(p << 1 | 1)) --s(p);
		fir(p) = fir(p << 1), las(p) = las(p << 1 | 1);
	}
	
	int ask(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return s(p);
		spread(p);
		int mid = (l(p) + r(p)) >> 1, ans = 0;
		if (l <= mid && r > mid)
		{
			ans = ask(p << 1, l, r) + ask(p << 1 | 1, l, r);
			if (las(p << 1) == fir(p << 1 | 1)) --ans;
		}
		else if (l <= mid) ans = ask(p << 1, l, r);
		else if (r > mid) ans = ask(p << 1 | 1, l, r);
		return ans;
	}
	int ask2(int p, int k)
	{
		if (l(p) == r(p) && r(p) == k) return fir(p);
		spread(p);
		int mid = (l(p) + r(p)) >> 1;
		if (k <= mid) return ask2(p << 1, k);
		else return ask2(p << 1 | 1, k);
	}
}

void dfs1(int now, int father, int depth)
{
	dep[now] = depth; fa[now] = father; Size[now] = 1;
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == father) continue;
		dfs1(u, now, depth + 1);
		Size[now] += Size[u];
		if (Size[u] > Size[Son[now]]) Son[now] = u; 
	}
}

void dfs2(int now, int top_father)
{
	id[now] = ++cnt; Top[now] = top_father; w[cnt] = wfir[now];
	if (!Son[now]) return ;
	dfs2(Son[now], top_father);
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa[now] || u == Son[now]) continue;
		dfs2(u, u);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) wfir[i] = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		Next[x].push_back(y), Next[y].push_back(x);
	}
	dfs1(1, 1, 1); dfs2(1, 1); Segment_tree::build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		char ch; std::cin >> ch;
		if (ch == 'C')
		{
			int a = read(), b = read(), c = read();
			while (Top[a] != Top[b])
			{
				if (dep[Top[a]] < dep[Top[b]]) std::swap(a, b);
				Segment_tree::change(1, id[Top[a]], id[a], c);
				a = fa[Top[a]];
			}
			if (dep[a] > dep[b]) std::swap(a, b);
			Segment_tree::change(1, id[a], id[b], c);
		}
		if (ch == 'Q')
		{
			int a = read(), b = read(), ans = 0;
			while (Top[a] != Top[b])
			{
				if (dep[Top[a]] < dep[Top[b]]) std::swap(a, b);
				ans += Segment_tree::ask(1, id[Top[a]], id[a]);
				if (Segment_tree::ask2(1, id[Top[a]]) == Segment_tree::ask2(1, id[fa[Top[a]]])) --ans;
				a = fa[Top[a]];
			}
			if (dep[a] > dep[b]) std::swap(a, b);
			ans += Segment_tree::ask(1, id[a], id[b]);
			printf("%d\n", ans);
		}
	}
	return 0;
}
