/*
========= Plozia =========
	Author:Plozia
	Problem:P2805 [NOI2009] 植物大战僵尸
	Date:2021/6/1
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXM = 1000000 + 10, MAXN = 10000 + 10, INF = 0x7f7f7f7f;
int n, m, val[MAXN], cnt_Edge = 1, Head[MAXN], cnt_tp = 1, tp_Head[MAXN], cnt[MAXN], s, t, cur[MAXN];
int dep[MAXN], gap[MAXN];
struct node { int to, val, Next; } tp[MAXM], Edge[MAXM];
bool book[MAXN];
//超源：n * m + 1, 超汇：n * m + 2

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
void tp_add(int x, int y, int z) { ++cnt_tp; tp[cnt_tp] = (node){y, z, tp_Head[x]}; tp_Head[x] = cnt_tp; }
int Change(int x, int y) { return (x - 1) * m + y; }

void Top_sort()
{
	queue <int> q;
	for (int i = 1; i <= n * m; ++i)
		if (cnt[i] == 0) { q.push(i); book[i] = 1; }
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = tp_Head[x]; i; i = tp[i].Next)
		{
			int u = tp[i].to; --cnt[u];
			if (cnt[u] == 0) { q.push(u); book[u] = 1; }
		}
	}
}

void bfs()
{
	queue <int> q;
	memset(dep, -1, sizeof(dep));
	q.push(t); dep[t] = 0; ++gap[0];
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
			int Minn = dfs(u, Min(Flow - used, Edge[i].val));
			if (Minn)
			{
				Edge[i].val -= Minn; Edge[i ^ 1].val += Minn; used += Minn;
				if (used == Flow) return used;
			}
		}
	}
	--gap[dep[now]];
	if (gap[dep[now]] == 0) dep[s] = n * m + 3;
	++dep[now]; ++gap[dep[now]];
	return used;
}

int ISAP()
{
	int ans = 0; bfs();
	while (dep[s] < n * m + 2) { for (int i = 1; i <= n * m + 5; ++i) cur[i] = Head[i]; ans += dfs(s, INF); }
	return ans;
}

int main()
{
	n = Read(), m = Read(); s = n * m + 1, t = n * m + 2;
	int sum = 0;
	for (int i = 1; i <= n * m; ++i)
	{
		val[i] = Read();
		int w = Read();
		while (w--)
		{
			int x = Read() + 1, y = Read() + 1;
			tp_add(i, Change(x, y), 0); ++cnt[Change(x, y)];
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = m; j > 1; --j)
			{ tp_add(Change(i, j), Change(i, j - 1), 0); ++cnt[Change(i, j - 1)]; }
	Top_sort();
	for (int i = 1; i <= n * m; ++i)
	{
		if (val[i] > 0 && book[i]) { add_Edge(s, i, val[i]); add_Edge(i, s, 0); }
		else if (book[i]) { add_Edge(i, t, -val[i]); add_Edge(t, i, 0); }
	}
	for (int i = 1; i <= n * m; ++i)
		if (book[i] && val[i] > 0) sum += val[i];
	for (int i = 1; i <= n * m; ++i)
	{
		if (book[i] == 0) continue ;
		for (int j = tp_Head[i]; j; j = tp[j].Next)
		{
			int u = tp[j].to;
			if (book[u] == 0) continue ;
			add_Edge(u, i, INF); add_Edge(i, u, 0);
		}
	}
	printf("%d\n", sum - ISAP());
	return 0;
}