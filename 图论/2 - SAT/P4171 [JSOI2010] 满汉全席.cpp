/*
========= Plozia =========
	Author:Plozia
	Problem:P4171 [JSOI2010] 满汉全席
	Date:2021/8/13
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5, MAXM = 4e3 + 5;
int t, n, m, Head[MAXN << 1], cnt_Edge = 1, Color[MAXN << 1], col, sta[MAXN << 1], Top;
bool book[MAXN << 1];
struct node { int to, val, Next; } Edge[MAXM];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void dfs1(int now)
{
	book[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
		{ int u = Edge[i].to; if (book[u] || Edge[i].val == 1) continue ; dfs1(u); }
	sta[++Top] = now;
}

void dfs2(int now)
{
	Color[now] = col, book[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
		{ int u = Edge[i].to; if (book[u] || Edge[i].val == 0) continue ; dfs2(u); }
}

int main()
{
	t = Read();
	while (t--)
	{
		memset(Head, 0, sizeof(Head)); memset(Color, 0, sizeof(Color));
		memset(Edge, 0, sizeof(Edge)); col = 0, cnt_Edge = 1, Top = 0;
		n = Read(), m = Read();
		for (int i = 1; i <= m; ++i)
		{
			char ch = getchar(); int flag1 = 0, flag2 = 0, p1, p2;
			while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
			if (ch == 'h') flag1 = 0; else flag1 = 1; p1 = Read();
			ch = getchar(); while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
			if (ch == 'h') flag2 = 0; else flag2 = 1; p2 = Read();
			if (flag1 == 0 && flag2 == 0) { add_Edge(p1 + n, p2, 0); add_Edge(p2, p1 + n, 1); add_Edge(p2 + n, p1, 0); add_Edge(p1, p2 + n, 1); }
			if (flag1 == 0 && flag2 == 1) { add_Edge(p1 + n, p2 + n, 0); add_Edge(p2 + n, p1 + n, 1); add_Edge(p2, p1, 0); add_Edge(p1, p2, 1); }
			if (flag1 == 1 && flag2 == 0) { add_Edge(p1, p2, 0); add_Edge(p2, p1, 1); add_Edge(p2 + n, p1 + n, 0); add_Edge(p1 + n, p2 + n, 1); }
			if (flag1 == 1 && flag2 == 1) { add_Edge(p1, p2 + n, 0); add_Edge(p2 + n, p1, 1); add_Edge(p2, p1 + n, 0); add_Edge(p1 + n, p2, 1); }
		}
		memset(book, 0, sizeof(book));
		for (int i = 1; i <= 2 * n; ++i)
			if (!book[i]) dfs1(i);
		std::reverse(sta + 1, sta + Top + 1); memset(book, 0, sizeof(book));
		for (int i = 1; i <= 2 * n; ++i)
			if (!book[sta[i]]) { ++col; dfs2(sta[i]); }
		bool flag = 0;
		for (int i = 1; i <= n; ++i)
			if (Color[i] == Color[i + n]) flag = 1;
		if (flag) printf("BAD\n"); else printf("GOOD\n");
	}
	return 0;
}