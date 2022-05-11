/*
========= Plozia =========
	Author:Plozia
	Problem:SP1437 PT07Z - Longest path in a tree
	Date:2021/4/27
	Another:树的直径模板题
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e4 + 10;
int n, Head[MAXN], cnt_Edge = 1, f[MAXN], ans, root, f1[MAXN], f2[MAXN];
struct node { int Next, to, val; } Edge[MAXN << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){ Head[x], y, z }; Head[x] = cnt_Edge; }

void dfs(int now, int father)
{
	if (f[now] > ans) { ans = f[now]; root = now; }
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		f[u] = f[now] + Edge[i].val;
		dfs(u, now);
	}
}

void Solve_DFS()
{
	root = 1;
	f[root] = 0; dfs(root, 0); ans = 0;
	f[root] = 0; dfs(root, 0);
	printf("%d\n", ans);
}

void DP(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		DP(u, now);
		if (f1[u] + Edge[i].val > f1[now]) { f2[now] = f1[now]; f1[now] = f1[u] + Edge[i].val; }
		else { f2[now] = Max(f2[now], f1[u] + Edge[i].val); }
	}
}

void Solve_DP()
{
	DP(1, 0);
	for (int i = 1; i <= n; ++i) ans = Max(ans, f1[i] + f2[i]);
	printf("%d\n", ans);
}

int main()
{
	n = read();
	for (int i = 1; i < n; ++i)
	{
		int u = read(), v = read();
		add_Edge(u, v, 1); add_Edge(v, u, 1);
	}
	// Solve_DFS(); return 0;
	Solve_DP(); return 0;
}