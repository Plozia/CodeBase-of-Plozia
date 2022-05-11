/*
========= Plozia =========
	Author:Plozia
	Problem:(次短路模板题)P2865 [USACO06NOV]Roadblocks G
	Date:2021/4/20
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 5000 + 10, MAXM = 100000 + 10;
int n, m, Head[MAXN], cnt_Edge = 1, dis[MAXN][2], ans, ans2 = 0x7f7f7f7f;
struct node { int to, val, Next; } Edge[MAXM << 1];
bool vis[MAXN];

struct cmp
{
	int x, y;
	bool operator <(const cmp &fir) const
	{
		return y > fir.y;
	}
};

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void dijkstra(int op)
{
	memset(vis, 0, sizeof(vis));
	priority_queue <cmp> q;
	if (op == 0) q.push((cmp){1, 0}), dis[1][op] = 0;
	else q.push((cmp){n, 0}), dis[n][op] = 0;
	while (!q.empty())
	{
		cmp x = q.top(); q.pop();
		if (vis[x.x]) continue ; vis[x.x] = 1;
		for (int i = Head[x.x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (dis[u][op] > dis[x.x][op] + Edge[i].val)
			{
				dis[u][op] = dis[x.x][op] + Edge[i].val;
				if (!vis[u]) q.push((cmp){u, dis[u][op]});
			}
		}
	}
}

int main()
{
	n = read(), m = read();
	memset(dis, 0x7f, sizeof(dis));
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	dijkstra(0); dijkstra(1); ans = dis[n][0];
	for (int i = 2; i <= cnt_Edge; i += 2)
	{
		int u = Edge[i ^ 1].to, v = Edge[i].to, z = Edge[i].val;
		int sum = dis[u][0] + dis[v][1] + z;
		if (sum > ans) ans2 = Min(ans2, sum);
		sum = dis[u][1] + dis[v][0] + z;
		if (sum > ans) ans2 = Min(ans2, sum);
	}
	printf("%d\n", ans2); return 0;
}