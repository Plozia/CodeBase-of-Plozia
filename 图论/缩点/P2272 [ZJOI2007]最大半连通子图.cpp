/*
========= Plozia =========
	Author:Plozia
	Problem:P2272 [ZJOI2007]最大半连通子图
	Date:2021/5/11
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 1e5 + 10, MAXM = 1e6 + 10;
int n, m, P, col[MAXN], Color, sta[MAXN], Top, cnt_a, cnt[MAXN], Size[MAXN];
LL f[MAXN], g[MAXN];
bool book[MAXN];

struct Graph
{
	int Head[MAXN], cnt_Edge = 1;
	struct node { int to, Next, val; } Edge[MAXM << 1];
	void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x], z}; Head[x] = cnt_Edge; }
}Old_Graph, New_Graph;

struct EDGE
{
	int x, y;
}a[MAXM];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
bool cmp(const EDGE &fir, const EDGE &sec) { return (fir.x ^ sec.x) ? (fir.x < sec.x) : (fir.y < sec.y); }

void dfs1(int now, int father)
{
	book[now] = 1;
	for (int i = Old_Graph.Head[now]; i; i = Old_Graph.Edge[i].Next)
	{
		int u = Old_Graph.Edge[i].to;
		if (book[u] || Old_Graph.Edge[i].val == 0) continue ;
		dfs1(u, now);
	}
	++Top; sta[Top] = now;
}

void dfs2(int now, int father, int c)
{
	col[now] = c; book[now] = 1;
	for (int i = Old_Graph.Head[now]; i; i = Old_Graph.Edge[i].Next)
	{
		int u = Old_Graph.Edge[i].to;
		if (book[u] || Old_Graph.Edge[i].val == 1) continue ;
		dfs2(u, now, c);
	}
}

void topsort()
{
	queue <int> q;
	for (int i = 1; i <= Color; ++i)
		if (!cnt[i]) { q.push(i); f[i] = Size[i]; g[i] = 1; }
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = New_Graph.Head[x]; i; i = New_Graph.Edge[i].Next)
		{
			int u = New_Graph.Edge[i].to;
			if (f[u] < f[x] + Size[u]) { f[u] = f[x] + Size[u]; g[u] = g[x] % (LL)P; }
			else if (f[u] == f[x] + Size[u]) { g[u] = (g[u] + g[x]) % (LL)P; }
			--cnt[u]; if (!cnt[u]) q.push(u);
		}
	}
}

int main()
{
	n = read(), m = read(), P = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		Old_Graph.add_Edge(x, y, 1); Old_Graph.add_Edge(y, x, 0);
	}
	for (int i = 1; i <= n; ++i)
		if (!book[i]) dfs1(i, i);
	std::reverse(sta + 1, sta + Top + 1);
	memset(book, 0, sizeof(book));
	for (int i = 1; i <= n; ++i)
		if (!book[sta[i]]) { ++Color; dfs2(sta[i], sta[i], Color); }
	for (int i = 2; i <= Old_Graph.cnt_Edge; i += 2)
	{
		int x = Old_Graph.Edge[i ^ 1].to, y = Old_Graph.Edge[i].to;
		if (col[x] != col[y]) { ++cnt_a; a[cnt_a].x = col[x]; a[cnt_a].y = col[y]; }
	}
	for (int i = 1; i <= n; ++i) ++Size[col[i]];
	std::sort(a + 1, a + cnt_a + 1, cmp);
	for (int i = 1; i <= cnt_a; ++i)
	{
		if (a[i].x == a[i - 1].x && a[i].y == a[i - 1].y) continue ;
		New_Graph.add_Edge(a[i].x, a[i].y, 0); ++cnt[a[i].y];
	}
	topsort();
	LL ans1 = 0, ans2 = 0;
	for (int i = 1; i <= Color; ++i)
	{
		if (f[i] > ans1) { ans1 = f[i]; ans2 = g[i]; }
		else if (f[i] == ans1) { ans2 = (ans2 + g[i]) % (LL)P; }
	}
	printf("%lld\n%lld\n", ans1, ans2); return 0;
}