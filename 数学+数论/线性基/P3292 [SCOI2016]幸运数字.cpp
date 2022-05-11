/*
========= Plozia =========
	Author:Plozia
	Problem:P3292 [SCOI2016]幸运数字
	Date:2021/7/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 20000 + 10;
int n, q, Head[MAXN], cnt_Edge = 1, fa[MAXN][21], dep[MAXN];
LL a[MAXN], p[MAXN][21][70], ans[70];
struct node { int to, Next; } Edge[MAXN << 1];

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void Add(LL *fir, LL x)
{
	for (int i = 61; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (x & fir[i]) x ^= fir[i];
			else { fir[i] = x; return ; }
		}
	}
}

void dfs(int now, int father, int depth)
{
	fa[now][0] = father; Add(p[now][0], a[now]); dep[now] = depth;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now, depth + 1);
	}
}

void Merge(LL *fir, LL *sec)
{
	for (int i = 61; i >= 0; --i)
		if (sec[i]) Add(fir, sec[i]);
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
		{
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			memcpy(p[i][j], p[i][j - 1], sizeof(p[i][j - 1]));
			Merge(p[i][j], p[fa[i][j - 1]][j - 1]);
		}
}

void LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) { Merge(ans, p[x][i]); x = fa[x][i]; }
	if (x == y) { Merge(ans, p[x][0]); return ; }
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) { Merge(ans, p[x][i]), Merge(ans, p[y][i]); x = fa[x][i], y = fa[y][i]; }
	Merge(ans, p[x][0]); Merge(ans, p[y][0]); Merge(ans, p[fa[x][0]][0]);
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); add_Edge(x, y); add_Edge(y, x); }
	dfs(1, 1, 1); init();
	while (q--)
	{
		int x = Read(), y = Read();
		memset(ans, 0, sizeof(ans));
		LCA(x, y); LL sum = 0;
		for (int i = 65; i >= 0; --i) sum = Max(sum, sum ^ ans[i]);
		printf("%lld\n", sum);
	}
	return 0;
}