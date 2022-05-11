/*
========= Plozia =========
	Author:Plozia
	Problem:P3384 ��ģ�塿�������ʷ�
	Date:2021/3/7
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, root, P, fa[MAXN], Son[MAXN], dep[MAXN], a[MAXN], cnt, Size[MAXN];
int id[MAXN], Top[MAXN], val[MAXN];
vector <int> Next[MAXN];

struct node
{
	int l, r;
	LL sum, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define a(p) tree[p].add
}tree[MAXN << 2];

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
		if (l == r) {s(p) = val[l]; return ;}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
	}
	
	void spread(int p)
	{
		if (a(p))
		{
			s(p << 1) = (s(p << 1) + ((LL)r(p << 1) - l(p << 1) + 1) * a(p)) % P;
			s(p << 1 | 1) = (s(p << 1 | 1) + ((LL)r(p << 1 | 1) - l(p << 1 | 1) + 1) * a(p)) % P;
			a(p << 1) += a(p); a(p << 1 | 1) += a(p); a(p) = 0;
		}
	}
	
	void add(int p, int l, int r, LL k)
	{
		if (l(p) >= l && r(p) <= r)
		{
			s(p) = (s(p) + k * (r(p) - l(p) + 1)) % P;
			a(p) += k; return ;
		}
		spread(p);
		int mid = (l(p) + r(p)) >> 1;
		if (l <= mid) add(p << 1, l, r, k);
		if (r > mid) add(p << 1 | 1, l, r, k);
		s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
	}
	
	LL ask(int p, int l, int r)
	{
		if (l(p) >= l && r(p) <= r) return s(p);
		spread(p); int mid = (l(p) + r(p)) >> 1; LL ans = 0;
		if (l <= mid) ans += ask(p << 1, l, r);
		if (r > mid) ans += ask(p << 1 | 1, l, r);
		return ans % P;
	}
}

void dfs1(int now, int father, int depth)//��ǰ�ڵ㣬���ף����
{
	dep[now] = depth;
	fa[now] = father;
	Size[now] = 1;//��¼��������
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == father) continue;
		dfs1(u, now, depth + 1);
		Size[now] += Size[u];//��¼������С
		if (Size[u] > Size[Son[now]]) Son[now] = u;//�����ض���
	}
}

void dfs2(int now, int top_father)
{
	id[now] = ++cnt;
	val[cnt] = a[now];
	Top[now] = top_father;
	if (!Son[now]) return ;
	dfs2(Son[now], top_father);
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa[now] || u == Son[now]) continue;
		dfs2(u, u);
	}
}

void add1(int x, int y, LL k)
{
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		Segment_tree::add(1, id[Top[x]], id[x], k);
		x = fa[Top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	Segment_tree::add(1, id[x], id[y], k);
}

LL ask1(int x, int y)
{
	LL ans = 0;
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		ans = (ans + Segment_tree::ask(1, id[Top[x]], id[x])) % P;
		x = fa[Top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	ans = (ans + Segment_tree::ask(1, id[x], id[y])) % P;
	return ans;
}

void add2(int x, LL k)
{
	Segment_tree::add(1, id[x], id[x] + Size[x] - 1, k);
}

LL ask2(int x)
{
	return Segment_tree::ask(1, id[x], id[x] + Size[x] - 1) % P;
}

int main()
{
	n = read(), m = read(), root = read(), P = read();
	for (int i = 1; i <= n; ++i) a[i] = read() % P;
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		Next[x].push_back(y), Next[y].push_back(x);
	}
	dfs1(root, root, 1); dfs2(root, root);
	Segment_tree::build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int opt = read();
		if (opt == 1)
		{
			int x = read(), y = read(), z = read() % P;
			add1(x, y, z);
		}
		if (opt == 2)
		{
			int x = read(), y = read();
			printf("%lld\n", ask1(x, y) % P);
		}
		if (opt == 3)
		{
			int x = read(), z = read() % P;
			add2(x, z);
		}
		if (opt == 4)
		{
			int x = read();
			printf("%lld\n", ask2(x) % P);
		}
	}
	return 0;
}
