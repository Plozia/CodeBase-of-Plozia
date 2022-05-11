/*
========= Plozia =========
	Author:Plozia
	Problem:P3698 [CQOI2017]小Q的棋盘
	Date:2021/5/25
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 10;
int n, v, f1[MAXN], f2[MAXN], Head[MAXN], cnt_Edge = 1, ans;
struct node { int to, val, Next; } Edge[MAXN << 1];

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

void dfs(int now, int father, int dis)
{
	if (dis > ans) ans = dis;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now, dis + 1);
	}
}

int main()
{
	n = Read(), v = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y, 1); add_Edge(y, x, 1);
	}
	dfs(0, -1, 1);
	if (ans > v) printf("%d\n", v + 1);
	else printf("%d\n", Min(n, (v + ans + 1) / 2));
	return 0;
}