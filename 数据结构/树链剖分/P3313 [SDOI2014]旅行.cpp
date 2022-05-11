/*
========= Plozia =========
	Author:Plozia
	Problem:P3313 [SDOI2014]旅行
	Date:2021/3/9
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using std::vector;
using std::string;

typedef long long LL;
const int MAXN = 1e5 + 10, MAXX = 2e6 + 10;
int n, q, wfir[MAXN], cfir[MAXN], w[MAXN], c[MAXN], root[MAXN], cnt;
int Son[MAXN], Size[MAXN], dep[MAXN], fa[MAXN], Top[MAXN], id[MAXN];
vector <int> Next[MAXN];
struct node
{
	int w, l, r, maxn;
}tree[MAXN + MAXX + 10];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

namespace Segment_tree
{
	void change(int p, int l, int r, int k, int v, int w)
	{
		if (l == r) {tree[p].w = tree[p].maxn = w; return ;}
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			if (!tree[p].l) tree[p].l = ++cnt;
			change(tree[p].l, l, mid, k, v, w);
		}
		else
		{
			if (!tree[p].r) tree[p].r = ++cnt;
			change(tree[p].r, mid + 1, r, k, v, w);
		}
		tree[p].w = tree[tree[p].l].w + tree[tree[p].r].w;
		tree[p].maxn = Max(tree[tree[p].l].maxn, tree[tree[p].r].maxn);
	}
	
	int ask_sum(int p, int l1, int r1, int l2, int r2)
	{
		if (l1 >= l2 && r1 <= r2) return tree[p].w;
		int mid = (l1 + r1) >> 1, ans = 0;
		if (l2 <= mid)
		{
			if (tree[p].l) ans += ask_sum(tree[p].l, l1, mid, l2, r2);
		}
		if (r2 > mid)
		{
			if (tree[p].r) ans += ask_sum(tree[p].r, mid + 1, r1, l2, r2);
		}
		return ans;
	}
	
	int ask_max(int p, int l1, int r1, int l2, int r2)
	{
		if (l1 >= l2 && r1 <= r2) return tree[p].maxn;
		int mid = (l1 + r1) >> 1, ans = 0;
		if (l2 <= mid)
		{
			if (tree[p].l) ans = std::max(ans, ask_max(tree[p].l, l1, mid, l2, r2));
		}
		if (r2 > mid)
		{
			if (tree[p].r) ans = std::max(ans, ask_max(tree[p].r, mid + 1, r1, l2, r2));
		}
		return ans;
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
	id[now] = ++cnt; Top[now] = top_father;
	w[cnt] = wfir[now]; c[cnt] = cfir[now];
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
	n = read(), q = read();
	for (int i = 1; i <= n; ++i) wfir[i] = read(), cfir[i] = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		Next[x].push_back(y), Next[y].push_back(x);
	}
	dfs1(1, 1, 1); dfs2(1, 1);
	for (int i = 1; i <= n; ++i) root[i] = i; cnt = n;
	for (int i = 1; i <= n; ++i) Segment_tree::change(root[c[i]], 1, n, i, c[i], w[i]);
	for (int i = 1; i <= q; ++i)
	{
		string str; std::cin >> str;
		if (str == "CC")//改宗教,x,c
		{
			int x = read(), c_ = read();
			Segment_tree::change(root[c[id[x]]], 1, n, id[x], c[id[x]], 0);
			c[id[x]] = c_;
			Segment_tree::change(root[c[id[x]]], 1, n, id[x], c[id[x]], w[id[x]]);
		}
		if (str == "CW")//改评级,x,w
		{
			int x = read(), w_ = read(); w[id[x]] = w_;
			Segment_tree::change(root[c[id[x]]], 1, n, id[x], c[id[x]], w[id[x]]);
		}
		if (str == "QS")//求总和,x,y
		{
			int x = read(), y = read(); int ans = 0, c_ = c[id[x]];
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				ans += Segment_tree::ask_sum(root[c_], 1, n, id[Top[x]], id[x]);
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			ans += Segment_tree::ask_sum(root[c_], 1, n, id[x], id[y]);
			printf("%d\n", ans);
		}
		if (str == "QM")//求最值,x,y
		{
			int x = read(), y = read(); int ans = 0, c_ = c[id[x]];
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				ans = std::max(ans, Segment_tree::ask_max(root[c_], 1, n, id[Top[x]], id[x]));
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			ans = std::max(ans, Segment_tree::ask_max(root[c_], 1, n, id[x], id[y]));
			printf("%d\n", ans);
		}
	}
	return 0;
}
