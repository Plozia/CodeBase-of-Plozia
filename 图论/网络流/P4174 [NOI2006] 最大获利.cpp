/*
========= Plozia =========
	Author:Plozia
	Problem:P4174 [NOI2006] 最大获利
	Date:2021/11/17
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 5000 + 5, MAXM = 50000 + 5, INF = 0x7f7f7f7f;
int n, m, Head[MAXN + MAXM], a[MAXN], s, t, cnt_Edge = 1, ans, sum, Dep[MAXN + MAXM], Gap[MAXN + MAXM], Cur[MAXN + MAXM];
struct node { int To, val, Next; } Edge[1000010];

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

void bfs()
{
	queue <int> q; for (int i = 1; i <= n + m + 2; ++i) Dep[i] = -1;
	q.push(t); Dep[t] = 1; Gap[1] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].To;
			if (Dep[u] != -1) continue ;
			Dep[u] = Dep[x] + 1; ++Gap[Dep[u]]; q.push(u);
		}
	}
}

int dfs(int now, int Flow)
{
	if (now == t || Flow == 0) return Flow; int Used = 0;
	for (int i = Cur[now]; i; i = Edge[i].Next)
	{
		Cur[now] = i; int u = Edge[i].To;
		if (Edge[i].val > 0 && Dep[now] == Dep[u] + 1)
		{
			int Spend = dfs(u, Min(Flow - Used, Edge[i].val));
			Edge[i].val -= Spend; Edge[i ^ 1].val += Spend; Used += Spend;
			if (Used == Flow) return Flow;
		}
	}
	--Gap[Dep[now]]; if (Gap[Dep[now]] == 0) Dep[s] = n + m + 3;
	++Dep[now]; ++Gap[Dep[now]]; return Used;
}

void ISAP()
{
	bfs();
	while (Dep[s] <= n + m + 2)
	{
		for (int i = 1; i <= n + m + 2; ++i) Cur[i] = Head[i];
		ans += dfs(s, INF);
	}
}

int main()
{
	n = Read(), m = Read(); s = n + m + 1; t = n + m + 2;
	for (int i = 1; i <= n; ++i) { a[i] = Read(); add_Edge(i, t, a[i]); add_Edge(t, i, 0); }
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(), v = Read(); sum += v;
		add_Edge(s, n + i, v); add_Edge(n + i, s, 0);
		add_Edge(n + i, x, INF); add_Edge(x, n + i, 0);
		add_Edge(n + i, y, INF); add_Edge(y, n + i, 0);
	}
	ISAP(); printf("%d\n", sum - ans); return 0;
}