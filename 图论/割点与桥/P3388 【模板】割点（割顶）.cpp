/*
========= Plozia =========
	Author:Plozia
	Problem:P3388 【模板】割点（割顶）
	Date:2021/5/10
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e4 + 10, MAXM = 1e5 + 10;
int n, m, Head[MAXN], cnt_Edge = 1, dfn[MAXN], Low[MAXN], cnt_node;
struct node { int to, Next; } Edge[MAXM << 1];
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){ y, Head[x] }; Head[x] = cnt_Edge; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void dfs(int now, int father)
{
	dfn[now] = Low[now] = ++cnt_node; int val = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (!dfn[u])
		{
			dfs(u, now); ++val;
			Low[now] = Min(Low[now], Low[u]);
			if (Low[u] >= dfn[now] && now != father) book[now] = 1;
		}
		Low[now] = Min(Low[now], dfn[u]);
	}
	if (now == father && val >= 2) book[now] = 1;
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
		if (!dfn[i]) dfs(i, i);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (book[i]) ++ans;
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i)
		if (book[i]) printf("%d ", i);
	printf("\n"); return 0;
}