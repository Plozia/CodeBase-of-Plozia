/*
========= Plozia =========
	Author:Plozia
	Problem:（暂无题目）【模板】桥
	Date:2021/5/10
	Remarks #1:本题的数据范围采用 P3388 的数据范围
	Remarks #2:因为没有数据验证，本代码不保证正确性
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e4 + 10, MAXM = 1e5 + 10;
int n, m, Head[MAXN], cnt_Edge = 1, Cut[MAXM << 1], Dfn[MAXN], Low[MAXN], cnt_node;
struct node { int to, Next; } Edge[MAXM << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void dfs(int now, int E)
{
	Dfn[now] = Low[now] = cnt_node;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (!Dfn[u])
		{
			dfs(u, i);
			Low[now] = Min(Low[now], Low[u]);
			if (Low[u] >= Dfn[now]) Cut[i] = Cut[i ^ 1] = 1;
		}
		else if (i != (E ^ 1)) Low[now] = Min(Low[now], Dfn[u]);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		add_Edge(x, y); add_Edge(y, x);
	}
	for (int i = 1; i <= n; ++i)
		if (!Dfn[i]) dfs(i, 0);
	int ans = 0;
	for (int i = 2; i <= cnt_Edge; i += 2)
		if (Cut[i]) ++ans;
	printf("%d\n", ans);
	for (int i = 2; i <= cnt_Edge; i += 2)
		if (Cut[i]) printf("%d %d\n", Edge[i ^ 1].to, Edge[i].to);
	return 0;
}