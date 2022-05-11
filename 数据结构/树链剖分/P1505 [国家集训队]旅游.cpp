/*
========= Plozia =========
	Author:Plozia
	Problem:P1505 [国家集训队]旅游
	Date:2021/3/12
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
#define Min(a, b) ((a < b) ? a : b)
using std::vector;
using std::string;

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, m, afir[MAXN];
int cnt, Top[MAXN], id[MAXN], fa[MAXN], dep[MAXN], Size[MAXN], Son[MAXN], a[MAXN];
struct Edge
{
	int x, y, z;
}e[MAXN];
struct node
{
	int l, r, sum, maxn, minn, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define maxn(p) tree[p].maxn
	#define minn(p) tree[p].minn
	#define a(p) tree[p].add
}tree[MAXN << 2];
vector <int> Next[MAXN], Num[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

namespace Segment_tree
{
	void build(int p, int l, int r)
	{
		l(p) = l, r(p) = r;
		if (l == r) {s(p) = maxn(p) = minn(p) = a[l]; return ;}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		s(p) = s(p << 1) + s(p << 1 | 1);
		maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
		minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
	}
	
	void spread(int p)
	{
		if (a(p) != 0)
		{
			a(p << 1) ^= 1; a(p << 1 | 1) ^= 1;
			s(p << 1) *= -1; s(p << 1 | 1) *= -1;
			int Maxn, Minn;
			Maxn = maxn(p << 1), Minn = minn(p << 1);
			minn(p << 1) = -Maxn, maxn(p << 1) = -Minn;
			Maxn = maxn(p << 1 | 1), Minn = minn(p << 1 | 1);
			minn(p << 1 | 1) = -Maxn, maxn(p << 1 | 1) = -Minn;
			a(p) = 0;
		}
	}
	
	void change_1(int p, int k, int w)
	{
		if (l(p) == r(p) && l(p) == k) {s(p) = maxn(p) = minn(p) = w; return ;}
		spread(p);
		int mid = (l(p) + r(p)) >> 1;
		if (k <= mid) change_1(p << 1, k, w);
		else change_1(p << 1 | 1, k, w);
		s(p) = s(p << 1) + s(p << 1 | 1);
		maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
		minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
	}
	
	void change_2(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r)
		{
			a(p) ^= 1; s(p) *= -1;
			int fir = maxn(p), sec = minn(p);
			minn(p) = fir * -1, maxn(p) = sec * -1; return ;
		}
		spread(p); int mid = (l(p) + r(p)) >> 1;
		if (l <= mid) change_2(p << 1, l, r);
		if (r > mid) change_2(p << 1 | 1, l, r);
		s(p) = s(p << 1) + s(p << 1 | 1);
		maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
		minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
	}
	
	int ask_sum(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return s(p);
		spread(p); int mid = (l(p) + r(p)) >> 1, ans = 0;
		if (l <= mid) ans += ask_sum(p << 1, l, r);
		if (r > mid) ans += ask_sum(p << 1 | 1, l, r);
		return ans;
	}
	
	int ask_maxn(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return maxn(p);
		spread(p); int mid = (l(p) + r(p)) >> 1, ans = -0x7f7f7f7f, tmp = -0x7f7f7f7f;
		if (l <= mid) {tmp = ask_maxn(p << 1, l, r); ans = Max(ans, tmp);}
		if (r > mid) {tmp = ask_maxn(p << 1 | 1, l, r); ans = Max(ans, tmp);}
		return ans;
	}
	
	int ask_minn(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return minn(p);
		spread(p); int mid = (l(p) + r(p)) >> 1, ans = 0x7f7f7f7f, tmp = 0x7f7f7f7f;
		if (l <= mid) {tmp = ask_minn(p << 1, l, r); ans = Min(ans, tmp);}
		if (r > mid) {tmp = ask_minn(p << 1 | 1, l, r); ans = Min(ans, tmp);}
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
	Top[now] = top_father; id[now] = ++cnt; a[cnt] = afir[now];
	if (!Son[now]) return ; dfs2(Son[now], top_father);
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa[now] || u == Son[now]) continue ;
		dfs2(u, u);
	}
}

int main()
{
	n = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read() + 1, y = read() + 1, z = read();
		e[i] = (Edge){x, y, z};
		Next[x].push_back(y), Next[y].push_back(x);
		Num[x].push_back(z), Num[y].push_back(z);
	}
	dfs1(1, 1, 1);
	for (int i = 1; i < n; ++i)
	{
		int x = e[i].x, y = e[i].y, z = e[i].z;
		if (dep[x] > dep[y]) afir[x] = z;
		else afir[y] = z;
	}//边权转点权
	dfs2(1, 1); Segment_tree::build(1, 1, n);
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		string str; std::cin >> str;
		if (str == "C")
		{
			int k = read(), w = read();
			Segment_tree::change_1(1, id[(dep[e[k].x] > dep[e[k].y]) ? e[k].x : e[k].y], w);
		}
		if (str == "N")
		{
			int x = read() + 1, y = read() + 1;
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				Segment_tree::change_2(1, id[Top[x]], id[x]);
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			if (x != y) Segment_tree::change_2(1, id[x] + 1, id[y]);
		}
		if (str == "SUM")
		{
			int x = read() + 1, y = read() + 1, ans = 0;
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				ans += Segment_tree::ask_sum(1, id[Top[x]], id[x]);
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			if (x != y) ans += Segment_tree::ask_sum(1, id[x] + 1, id[y]);
			printf("%d\n", ans);
		}
		if (str == "MAX")
		{
			int x = read() + 1, y = read() + 1, ans = -0x7f7f7f7f, tmp = -0x7f7f7f7f;
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				tmp = Segment_tree::ask_maxn(1, id[Top[x]], id[x]); ans = Max(ans, tmp);
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			if (x != y) {tmp = Segment_tree::ask_maxn(1, id[x] + 1, id[y]); ans = Max(ans, tmp);}
			printf("%d\n", (ans == -0x7f7f7f7f) ? 0 : ans);
		}
		if (str == "MIN")
		{
			int x = read() + 1, y = read() + 1, ans = 0x7f7f7f7f, tmp = 0x7f7f7f7f;
			while (Top[x] != Top[y])
			{
				if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
				tmp = Segment_tree::ask_minn(1, id[Top[x]], id[x]); ans = Min(ans, tmp);
				x = fa[Top[x]];
			}
			if (dep[x] > dep[y]) std::swap(x, y);
			if (x != y) {tmp = Segment_tree::ask_minn(1, id[x] + 1, id[y]); ans = Min(ans, tmp);}
			printf("%d\n", (ans == 0x7f7f7f7f) ? 0 : ans);
		}
	}
	return 0;
}
