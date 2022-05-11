/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#1——P2756 飞行员配对方案问题
	Date:2021/3/21
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 100 + 10, MAXM = 15000 + 10, INF = 0x7f7f7f7f;
int n, m, s, t, dep[MAXN], gap[MAXN], Head[MAXM << 1], cnt_Edge = 1, ans, cur[MAXN];
struct edge {int to, val, Next;} Edge[MAXM << 1];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int x, int y, int z) {Edge[++cnt_Edge] = (edge){y, z, Head[x]}; Head[x] = cnt_Edge;}
int Min(int fir, int sec) {return (fir < sec) ? fir : sec;}

void bfs()
{
	queue <int> q; q.push(t);
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	dep[t] = 0; ++gap[0];
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (dep[u] != -1) continue ;
			dep[u] = dep[x] + 1; ++gap[dep[u]]; q.push(u);
		}
	}
}

int dfs(int now, int Flow)
{
	if (now == t) return Flow;
	int used = 0;
	for (int i = cur[now]; i; i = Edge[i].Next)
	{
		cur[now] = i; int u = Edge[i].to;
		if (Edge[i].val && dep[now] == dep[u] + 1)
		{
			int Minn = dfs(u, Min(Edge[i].val, Flow - used));
			if (Minn)
			{
				Edge[i].val -= Minn; Edge[i ^ 1].val += Minn; used += Minn;
				if (used == Flow) return used;
			}
		}
	}
	--gap[dep[now]];
	if (!gap[dep[now]]) dep[s] = n + 1;
	++dep[now]; ++gap[dep[now]];
	return used;
}

int main()
{
	m = read(), n = read(); s = n + 1; t = n + 2;
	for (; ; )
	{
		int x = read(), y = read();
		if (x == -1 && y == -1) break;
		add_Edge(x, y, 1); add_Edge(y, x, 0);
	}
	for (int i = 1; i <= m; ++i) {add_Edge(s, i, 1); add_Edge(i, s, 0);}
	for (int i = m + 1; i <= n; ++i) {add_Edge(i, t, 1); add_Edge(t, i, 0);}
	bfs(); while (dep[s] < n + 2) {for (int i = 1; i <= n + 2; ++i) cur[i] = Head[i]; ans += dfs(s, INF);}
	printf("%d\n", ans);
	for (int i = 2; i <= cnt_Edge; i += 2)
	{
		if ((Edge[i].to != s && Edge[i].to != t) && (Edge[i ^ 1].to != s && Edge[i ^ 1].to != t))
			if (Edge[i ^ 1].val) printf("%d %d\n", Edge[i ^ 1].to, Edge[i].to);
	}
	return 0;
}
