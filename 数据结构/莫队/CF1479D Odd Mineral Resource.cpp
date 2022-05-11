/*
========= Plozia =========
	Author:Plozia
	Problem:CF1479D Odd Mineral Resource
	Date:2021/7/21
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, m, Head[MAXN], cnt_Edge = 1, cnt_n, Eular[MAXN << 1], a[MAXN], fa[MAXN][21], Block, Num_Block, dep[MAXN], ys[MAXN << 1], val[MAXN], sum[MAXN], fir[MAXN], las[MAXN], ans[MAXN], book[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];
struct Query { int x, y, l, r, id, lca; } q[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10)+ (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }
bool cmp(const Query &fir, const Query &sec) { return (ys[fir.x] ^ ys[sec.x]) ? (fir.x < sec.x) : ((ys[fir.x] & 1) ? (fir.y < sec.y) : (fir.y > sec.y)); }

void dfs(int now, int father)
{
	Eular[++cnt_n] = now, fa[now][0] = father; fir[now] = cnt_n; dep[now] = dep[father] + 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
	}
	Eular[++cnt_n] = now; las[now] = cnt_n;
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void Add(int x)
{
	++val[a[x]];
	if (val[a[x]] & 1) ++sum[(a[x] - 1) / Num_Block + 1];
	else --sum[(a[x] - 1) / Num_Block + 1];
}

void Del(int x)
{
	--val[a[x]];
	if (val[a[x]] & 1) ++sum[(a[x] - 1) / Num_Block + 1];
	else --sum[(a[x] - 1) / Num_Block + 1];
}

void Work(int x)
{
	book[x] ? Del(x) : Add(x);
	book[x] ^= 1;
}

int Ask(int l, int r)
{
	int yl = (l - 1) / Num_Block + 1, yr = (r - 1) / Num_Block + 1;
	if (yl == yr)
	{
		for (int i = l; i <= r; ++i)
			if (val[i] & 1) return i;
		return -1;
	}
	int el = yl * Num_Block, br = (yr - 1) * Num_Block + 1;
	for (int i = l; i <= el; ++i)
		if (val[i] & 1) return i;
	for (int i = br; i <= r; ++i)
		if (val[i] & 1) return i;
	for (int i = yl + 1; i <= yr - 1; ++i)
	{
		if (sum[i])
		{
			l = (i - 1) * Num_Block + 1, r = i * Num_Block;
			for (int j = l; j <= r; ++j)
				if (val[j] & 1) return j;
		}
	}
	return -1;
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); add_Edge(x, y); add_Edge(y, x); }
	dfs(1, 1); init(); Block = cnt_n / sqrt(m); Num_Block = sqrt(n);
	for (int i = 1; i <= cnt_n; ++i) ys[i] = (i - 1) / Block + 1;//cnt_n=2n
	for (int i = 1; i <= m; ++i)
	{
		q[i].x = Read(), q[i].y = Read(), q[i].l = Read(), q[i].r = Read(), q[i].id = i;
		q[i].lca = LCA(q[i].x, q[i].y);
		if (fir[q[i].x] > fir[q[i].y]) std::swap(q[i].x, q[i].y);
		if (q[i].x == q[i].lca) { q[i].x = fir[q[i].x]; q[i].y = fir[q[i].y]; q[i].lca = 0; }
		else { q[i].x = las[q[i].x]; q[i].y = fir[q[i].y]; }
	}
	std::sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		while (l > q[i].x) Work(Eular[--l]);
		while (r < q[i].y) Work(Eular[++r]);
		while (l < q[i].x) Work(Eular[l++]);
		while (r > q[i].y) Work(Eular[r--]);
		if (q[i].lca) Work(q[i].lca);
		ans[q[i].id] = Ask(q[i].l, q[i].r);
		if (q[i].lca) Work(q[i].lca);
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}