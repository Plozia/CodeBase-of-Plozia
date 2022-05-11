/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#5——P1251 餐巾计划问题
	Date:2021/3/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 2000 + 10, MAXM = 2000 * 12 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, r[MAXN], New_Spend, fast_Day, fast_Spend, Slow_Day, Slow_Spend, s, t, Head[MAXN << 1], cnt_Edge = 1, cur[MAXN << 1];
LL dis[MAXN << 1], ans;
bool book[MAXN << 1], vis[MAXN << 1];
struct node {int to; LL Flow, val; int Next;} Edge[MAXM];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int u, int v, LL w, LL c) {++cnt_Edge; Edge[cnt_Edge] = (node){v, w, c, Head[u]}; Head[u] = cnt_Edge;}
LL Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}

bool SPFA()
{
	queue <int> q; q.push(s);
	memset(book, 0, sizeof(book));
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0; book[s] = 1;
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
	return dis[t] < INF;
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
				ans += Minn * Edge[i].val; if (used == Flow) {vis[now] = 0; return used;}
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
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= 2 * n + 2; ++i) cur[i] = Head[i];
		while (dfs(s, INF) != 0) ;
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) r[i] = read();
	New_Spend = read(), fast_Day = read(), fast_Spend = read(), Slow_Day = read(), Slow_Spend = read();
	s = n * 2 + 1, t = n * 2 + 2;
	for (int i = 1; i <= n; ++i)
	{
		add_Edge(s, i, r[i], 0); add_Edge(i, s, 0, 0);
		add_Edge(i + n, t, r[i], 0); add_Edge(t, i + n, 0, 0);
	}
	for (int i = 1; i <= n; ++i)
	{
		add_Edge(s, i + n, INF, New_Spend); add_Edge(i + n, s, 0, -New_Spend);
		if (i != n) {add_Edge(i, i + 1, INF, 0); add_Edge(i + 1, i, 0, 0);}
		if (i + fast_Day <= n) {add_Edge(i, i + n + fast_Day, INF, fast_Spend); add_Edge(i + n + fast_Day, i, 0, -fast_Spend);}
		if (i + Slow_Day <= n) {add_Edge(i, i + n + Slow_Day, INF, Slow_Spend); add_Edge(i + n + Slow_Day, i, 0, -Slow_Spend);}
	}
	dinic(); printf("%lld\n", ans);
	return 0;
}