/*
========= Plozia =========
	Author:Plozia
	Problem:P3379 ��ģ�塿����������ȣ�LCA��
	Date:2021/3/18
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e5 + 10;
int n, m, root, cnt, Head[MAXN];
int Son[MAXN], Size[MAXN], dep[MAXN], fa[MAXN], Top[MAXN];
struct node {int to, Next;} Edge[MAXN << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int x, int y) {Edge[++cnt] = (node){y, Head[x]}; Head[x] = cnt;}

void dfs1(int now, int father, int depth)
{
	Size[now] = 1; fa[now] = father; dep[now] = depth;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue;
		dfs1(u, now, depth + 1);
		Size[now] += Size[u];
		if (Size[u] > Size[Son[now]]) Son[now] = u;
	}
}
void dfs2(int now, int top_father)
{
	Top[now] = top_father;
	if (!Son[now]) return ; dfs2(Son[now], top_father);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == Son[now] || u == fa[now]) continue;
		dfs2(u, u);
	}
}

int LCA(int x, int y)
{
	while (Top[x] != Top[y])
	{
		if (dep[Top[x]] < dep[Top[y]]) std::swap(x, y);
		x = fa[Top[x]];
	}
	return (dep[x] < dep[y]) ? x : y;
}

int main()
{
	n = read(), m = read(), root = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		add_Edge(x, y); add_Edge(y, x);
	}
	dfs1(root, root, 1); dfs2(root, root);
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		printf("%d\n", LCA(x, y));
	}
	return 0;
}
