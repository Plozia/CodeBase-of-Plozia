/*
========= Plozia =========
	Author:Plozia
	Problem:P4782 【模板】2-SAT 问题
	Date:2021/8/12
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 5;
int n, m, Head[MAXN << 1], cnt_Edge = 1, Color[MAXN << 1], col, sta[MAXN << 1], Top;
struct node { int To, val, Next; } Edge[MAXN << 2];
bool book[MAXN << 1];

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

void dfs1(int now)
{
	book[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (book[u] || Edge[i].val == 1) continue ;
		dfs1(u);
	}
	sta[++Top] = now;
}

void dfs2(int now)
{
	Color[now] = col, book[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (book[u] || Edge[i].val == 0) continue ;
		dfs2(u);
	}
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= m; ++i)
	{
		int x1 = Read(), p1 = Read(), x2 = Read(), p2 = Read();
		if (p1 == 1 && p2 == 1)
		{
			add_Edge(x1, x2 + n, 0); add_Edge(x2 + n, x1, 1);
			add_Edge(x2, x1 + n, 0); add_Edge(x1 + n, x2, 1);
		}
		if (p1 == 1 && p2 == 0)
		{
			add_Edge(x1, x2, 0); add_Edge(x2, x1, 1);
			add_Edge(x2 + n, x1 + n, 0); add_Edge(x1 + n, x2 + n, 1);
		}
		if (p1 == 0 && p2 == 1)
		{
			add_Edge(x1 + n, x2 + n, 0); add_Edge(x2 + n, x1 + n, 1);
			add_Edge(x2, x1, 0); add_Edge(x1, x2, 1);
		}
		if (p1 == 0 && p2 == 0)
		{
			add_Edge(x1 + n, x2, 0); add_Edge(x2, x1 + n, 1);
			add_Edge(x2 + n, x1, 0); add_Edge(x1, x2 + n, 1);
		}
	}
	for (int i = 1; i <= 2 * n; ++i)
		if (!book[i]) dfs1(i);
	std::reverse(sta + 1, sta + Top + 1); memset(book, 0, sizeof(book));
	for (int i = 1; i <= 2 * n; ++i)
		if (!book[sta[i]]) { ++col; dfs2(sta[i]); }
	for (int i = 1; i <= n; ++i)
		if (Color[i] == Color[i + n]) { printf("IMPOSSIBLE\n"); return 0; }
	printf("POSSIBLE\n");
	for (int i = 1; i <= n; ++i)
		if (Color[i] > Color[i + n]) printf("0 ");
		else printf("1 ");
	printf("\n"); return 0;
}