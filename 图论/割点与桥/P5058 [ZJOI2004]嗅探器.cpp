/*
========= Plozia =========
	Author:Plozia
	Problem:P5058 [ZJOI2004]嗅探器
	Date:2021/5/11
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 10, MAXM = 5e5 + 10;
int n, cnt_Edge = 1, Head[MAXN], dfn[MAXN], Low[MAXN], book[MAXN], s, t, cnt_node;
struct node { int to, Next; } Edge[MAXM << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

bool dfs(int now, int father)
{
	++cnt_node; dfn[now] = Low[now] = cnt_node;
	bool pd = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		bool flag = 0;
		if (!dfn[u])
		{
			flag = dfs(u, now); pd |= flag;
			Low[now] = Min(Low[u], Low[now]);
			if (Low[u] >= dfn[now] && now != father && flag) book[now] = 1;
		}
		Low[now] = Min(Low[now], dfn[u]);
	}
	if (now == t) return 1;
	else return pd;
}

int main()
{
	n = read();
	for (; ; )
	{
		int x = read(), y = read();
		if (x == y && x == 0) break ;
		add_Edge(x, y); add_Edge(y, x);
	}
	s = read(), t = read();
	bool Plozia_hug_zero = dfs(s, s);
	for (int i = 1; i <= n; ++i)
		if (book[i]) { printf("%d\n", i); return 0; }
	printf("No solution\n"); return 0;
}