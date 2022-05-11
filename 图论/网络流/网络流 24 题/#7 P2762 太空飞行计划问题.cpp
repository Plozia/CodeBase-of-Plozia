/*
========= Plozia =========
	Author:Plozia
	Problem:P2762 太空飞行计划问题
	Date:2021/5/27
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::cin;
using std::queue;

typedef long long LL;
const int MAXN = 150 + 10;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, m, Head[MAXN], cnt_Edge = 1, val[MAXN], Cost[MAXN];
int dep[MAXN], gap[MAXN], cur[MAXN];
LL ans;
bool book1[MAXN], book2[MAXN];
struct node { int to, val, Next; } Edge[300000], EEdge[300000];
//超源：n + m + 1，超汇：n + m + 2

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x], z}; Head[x] = cnt_Edge; }

void bfs()
{
	queue <int> q;
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	dep[n + m + 2] = 1; gap[1] = 1; q.push(n + m + 2);
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to; if (dep[u] != -1 && Edge[i].val != -114514) continue ;
			dep[u] = dep[x] + 1; ++gap[dep[u]]; q.push(u);
		}
	}
}

LL dfs(int now, LL Flow)
{
	if (now == n + m + 2) return Flow;
	LL used = 0;
	for (int i = cur[now]; i; i = Edge[i].Next)
	{
		cur[now] = i; int u = Edge[i].to;
		if (Edge[i].val && dep[now] == dep[u] + 1)
		{
			LL Minn = dfs(u, Min(Edge[i].val, Flow - used));
			if (Minn)
			{
				Edge[i].val -= Minn; Edge[i ^ 1].val += Minn; used += Minn;
				if (used == Flow) return used;
			}
		}
	}
	--gap[dep[now]];
	if (gap[dep[now]] == 0) dep[n + m + 1] = n + m + 2 + 1;
	++dep[now]; ++gap[dep[now]]; return used;
}

void ISAP()
{
	bfs(); ans = 0;
	while (dep[n + m + 1] < n + m + 2) { memcpy(Head, cur, sizeof(cur)); ans += dfs(n + m + 1, INF); }
}

int main()
{
	LL sum = 0;
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &val[i]); sum += (LL)val[i];
		char tools[10000];
		memset(tools, 0, sizeof tools);
		cin.getline(tools, 10000);
		int ulen = 0, tool;
		while (sscanf(tools + ulen, "%d", &tool) == 1)
		{
			add_Edge(i, n + tool, INF); add_Edge(n + tool, i, 0);
			if (tool == 0) ++ulen;
			else while (tool) { tool /= 10; ++ulen; }
			++ulen;
		}
	}
	for (int i = 1; i <= m; ++i) Cost[i] = Read();
	for (int i = 1; i <= n; ++i) { add_Edge(n + m + 1, i, val[i]); add_Edge(i, n + m + 1, 0); }
	for (int i = 1; i <= m; ++i) { add_Edge(n + i, n + m + 2, Cost[i]); add_Edge(n + m + 2, n + i, 0); }
	memcpy(EEdge, Edge, sizeof(EEdge));
	ISAP(); LL anss = ans;
	for (int i = 1; i <= m; ++i)
	{
		for (int j = Head[i + n]; j; j = Edge[j].Next)
		{
			int u = Edge[j].to;
			if (u == n + m + 2)
			{
				memcpy(EEdge, Edge, sizeof(Edge));
				Edge[j].val = Edge[j ^ 1].val = -114514;
				ISAP();
				if (anss - ans == EEdge[j].val) book2[i] = 1;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		int s1 = -1, s2 = 0;
		for (int j = Head[i]; j; j = Edge[j].Next)
		{
			++s1; int u = Edge[i].to;
			if (book2[u]) ++s2;
		}
		if (s2 == s1) book1[i] = 1;
	}
	for (int i = 1; i <= n; ++i)
		if (book1[i]) printf("%d ", i);
	printf("\n");
	for (int i = 1; i <= n; ++i)
		if (book2[i]) printf("%d ", i);
	printf("\n"); printf("%lld\n", sum - anss); return 0;
}