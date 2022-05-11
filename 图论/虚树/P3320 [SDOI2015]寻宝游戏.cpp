/*
========= Plozia =========
	Author:Plozia
	Problem:P3320 [SDOI2015]寻宝游戏
	Date:2021/12/14
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::set;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, Head[MAXN], cnt_Edge = 1, fa[MAXN][21], dep[MAXN], dfn[MAXN], ys[MAXN];
LL g[MAXN][21], ans;
bool book[MAXN];
struct node { int To, val, Next; } Edge[MAXN << 1];
set <int> s;
set <int> :: iterator it1, it2, it3;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	fa[now][0] = father; dep[now] = dep[father] + 1; dfn[now] = ++dfn[0]; ys[dfn[0]] = now;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		g[u][0] = Edge[i].val; dfs(u, now);
	}
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
		{
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			g[i][j] = g[i][j - 1] + g[fa[i][j - 1]][j - 1];
		}
}

LL Ask(int x, int y)
{
	LL val = 0;
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) { val += g[x][i]; x = fa[x][i]; }
	if (x == y) return val;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) { val += g[x][i] + g[y][i]; x = fa[x][i]; y = fa[y][i]; }
	return val + g[x][0] + g[y][0];
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	dfs(1, 1); init();
	for (int i = 1; i <= q; ++i)
	{
		int x = Read();
		if (book[x])
		{
			book[x] = 0; it1 = s.lower_bound(dfn[x]); it2 = s.upper_bound(dfn[x]);
			it3 = s.end(); int p1, p2;
			if (it1 != s.begin()) p1 = *(--it1); else p1 = *(--it3);
			if (it2 != s.end()) p2 = *it2; else p2 = *s.begin();
			ans = ans - Ask(ys[p1], x) - Ask(ys[p2], x) + Ask(ys[p1], ys[p2]);
			printf("%lld\n", ans); s.erase(dfn[x]);
		}
		else
		{
			s.insert(dfn[x]); it1 = s.lower_bound(dfn[x]); it2 = s.upper_bound(dfn[x]);
			book[x] = 1; it3 = s.end(); int p1, p2;
			if (it1 != s.begin()) p1 = *(--it1); else p1 = *(--it3);
			if (it2 != s.end()) p2 = *it2; else p2 = *s.begin();
			ans = ans + Ask(ys[p1], x) + Ask(ys[p2], x) - Ask(ys[p1], ys[p2]);
			printf("%lld\n", ans);
		}
	}
	return 0;
}