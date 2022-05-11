/*
========= Plozia =========
	Author:Plozia
	Problem:P3629 [APIO2010]巡逻
	Date:2021/4/28
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100000 + 10;
int n, k, Head[MAXN], cnt_Edge = 1, ans1, ans2, f1[MAXN], f2[MAXN], Tag1, Tag2, fa[MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){ y, z, Head[x]}; Head[x] = cnt_Edge; }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

void dfs(int now, int father, int flag)
{
	if (flag == 2) fa[now] = father;
	if (f1[now] > ans1)
	{
		ans1 = f1[now];
		if (flag == 1) Tag1 = now;
		else Tag2 = now;
	}
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		f1[u] = f1[now] + Edge[i].val;
		dfs(u, now, flag);
	}
}

void Solve_fir()
{
	memset(f1, 0, sizeof(f1)); ans1 = 0; Tag1 = 1;
	f1[Tag1] = 0; dfs(Tag1, 0, 1); ans1 = 0;
	f1[Tag1] = 0; dfs(Tag1, -1, 2);
}

void Deal_Edge()
{
	int p = Tag2;
	while (p != -1)
	{
		for (int i = Head[p]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (u == fa[p]) { Edge[i].val = -1; Edge[i ^ 1].val = -1; }
		}
		p = fa[p];
	}
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

void Solve_sec()
{
	memset(f1, 0, sizeof(f1));
	memset(f2, 0, sizeof(f2));
	DP(1, 0); ans2 = 0;
	for (int i = 1; i <= n; ++i) ans2 = Max(ans2, f1[i] + f2[i]);
}

int main()
{
	n = read(), k = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		add_Edge(x, y, 1); add_Edge(y, x, 1);
	}
	Solve_fir();
	if (k == 1) { printf("%d\n", 2 * (n - 1) - ans1 + 1); return 0; }
	Deal_Edge(); Solve_sec();
	printf("%d\n", 2 * (n - 1) - (ans1 - 1) - (ans2 - 1)); return 0;
}