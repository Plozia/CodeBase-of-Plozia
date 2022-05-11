/*
========= Plozia =========
	Author:Plozia
	Problem:CF1485E Move and Swap
	Date:2021/6/24
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 2e5 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int t, n, Head[MAXN], cnt_Edge = 1, dep[MAXN], depth, fa[MAXN];
LL a[MAXN], f[MAXN], Minn[MAXN], Maxn[MAXN], ans;
struct node { int to, Next; } Edge[MAXN << 1];
vector <int> v[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	dep[now] = dep[father] + 1; v[dep[now]].push_back(now); fa[now] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to; if (u == father) continue ;
		depth = Max(depth, dep[now] + 1);
		Minn[dep[now] + 1] = Min(Minn[dep[now] + 1], a[u]);
		Maxn[dep[now] + 1] = Max(Maxn[dep[now] + 1], a[u]);
		dfs(u, now);
	}
}

void DP()
{
	for (int i = 2; i <= depth; ++i)
	{
		LL Maxnuma = -INF, Maxnumb = -INF;
		for (int j = 0; j < v[i].size(); ++j)
		{
			Maxnuma = Max(Maxnuma, f[fa[v[i][j]]] + a[v[i][j]]);
			Maxnumb = Max(Maxnumb, f[fa[v[i][j]]] - a[v[i][j]]);
		}
		for (int j = 0; j < v[i].size(); ++j)
		{
			f[v[i][j]] = Max(Max(f[v[i][j]], f[fa[v[i][j]]] + Max(Maxn[i] - a[v[i][j]], a[v[i][j]] - Minn[i])), Max(Maxnuma - a[v[i][j]], a[v[i][j]] - Maxnumb));
			ans = Max(ans, f[v[i][j]]);
		}
	}
}

int main()
{
	t = Read();
	while (t--)
	{
		for (int i = 1; i <= n; ++i) Head[i] = 0, fa[i] = 0, v[i].clear();
		for (int i = 2; i <= cnt_Edge; ++i) Edge[i].to = Edge[i].Next = 0;
		n = Read(); ans = 0; depth = 0; cnt_Edge = 1;
		for (int i = 2; i <= n; ++i)
		{
			int x = Read();
			add_Edge(i, x); add_Edge(x, i);
		}
		for (int i = 2; i <= n; ++i) a[i] = Read();
		for (int i = 1; i <= n; ++i) f[i] = Maxn[i] = 0, Minn[i] = INF;
		dfs(1, 0); DP(); printf("%lld\n", ans);
	}
	return 0;
}