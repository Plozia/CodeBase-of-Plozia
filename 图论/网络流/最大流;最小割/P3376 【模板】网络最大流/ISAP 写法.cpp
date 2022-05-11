/*
========= Plozia =========
	Author:Plozia
	Problem:P3376 【模板】网络最大流——ISAP 写法
	Date:2021/3/19
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 200 + 10, MAXM = 5000 + 10;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, m, s, t, dep[MAXN], gap[MAXN], cnt_Edge = 1, Head[MAXM << 1], cur[MAXN];
struct node {int to; LL val; int Next;} Edge[MAXM << 1];
int q[MAXN], l, r;
LL ans;

int read()
{
	int sum = 0, fh = 1; char ch= getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
LL Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}
void add_Edge(int x, int y, int z) {Edge[++cnt_Edge] = (node){y, (LL)z, Head[x]}; Head[x] = cnt_Edge;}

void bfs()
{
	q[l = r = 1] = t;
	memset(dep, -1, sizeof(dep)); dep[t] = 0; ++gap[0];
	while (l <= r)
	{
		int x = q[l++];
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (dep[u] != -1) continue ;
			dep[u] = dep[x] + 1; q[++r] = u; ++gap[dep[u]];
		}
	}
}

LL dfs(int now, LL Flow)
{
	if (now == t) return Flow;
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
	if (gap[dep[now]] == 0) dep[s] = n + 1;
	++dep[now]; ++gap[dep[now]];
	return used;
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read();
		add_Edge(x, y, z); add_Edge(y, x, 0);
	}
	bfs();
	while (dep[s] <= n) {for (int i = 1; i <= n; ++i) cur[i] = Head[i]; ans += dfs(s, INF);}
	printf("%lld\n", ans);
	return 0;
}