/*
========= Plozia =========
	Author:Plozia
	Problem:P3381 【模板】最小费用最大流——dinic 写法
	Date:2021/3/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 5e3 + 10, MAXM = 5e4 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, m, s, t, Head[MAXN], cnt_Edge = 1, cur[MAXN];
LL dis[MAXN], ans_Flow, ans_Spend;
bool book[MAXN], vis[MAXN];
struct node{int to; LL Flow, val; int Next;} Edge[MAXM << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int u, int v, int w, int c) {++cnt_Edge; Edge[cnt_Edge] = (node){v, w, c, Head[u]}; Head[u] = cnt_Edge;}
LL Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}

bool SPFA()
{
	queue <int> q; q.push(s);
	memset(book, 0, sizeof(book));
	memset(dis, 0x3f, sizeof(dis));
	book[s] = 1; dis[s] = 0;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].Flow && dis[u] > dis[x] + Edge[i].val)
			{
				dis[u] = dis[x] + Edge[i].val;
				if (!book[u]) {q.push(u); book[u] = 1;}
			}
		}
	}
	return dis[t] != INF;
}

LL dfs(int now, LL Flow)
{
	if (now == t || Flow == 0) return Flow;
	vis[now] = 1; LL used = 0;
	for (int i = cur[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to; cur[now] = i;
		if (Edge[i].Flow && !vis[u] && dis[now] + Edge[i].val == dis[u])
		{
			LL Minn = dfs(u, Min(Flow - used, Edge[i].Flow));
			if (Minn)
			{
				Edge[i].Flow -= Minn; Edge[i ^ 1].Flow += Minn; used += Minn;
				ans_Spend += Edge[i].val * Minn; if (used == Minn) {vis[now] = 0; return used;}
			}
		}
	}
	vis[now] = 0;
	if (used == 0) vis[now] = 1;
	return used;
}

void dinic()
{
	while (SPFA())
	{
		LL d; memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; ++i) cur[i] = Head[i];
		while ((d = dfs(s, INF)) != 0) {ans_Flow += d;}
	}
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int u = read(), v = read(), w = read(), c = read();
		add_Edge(u, v, w, c); add_Edge(v, u, 0, -c);
	}
	dinic(); printf("%lld %lld\n", ans_Flow, ans_Spend);
	return 0;
}