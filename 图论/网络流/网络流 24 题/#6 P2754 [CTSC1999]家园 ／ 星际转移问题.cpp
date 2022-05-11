/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#6——P2754 [CTSC1999]家园 / 星际转移问题
	Date:2021/3/30
========= Plozia =========
*/

#include <bits/stdc++.h>
#define int long long
using std::vector;
using std::queue;

typedef long long LL;
const int MAXN = 15 * 700 + 10, MAXM = 2000000, INF = 0x3f3f3f3f;
int n, m, k, h[15 + 10], Time, Head[MAXN], s, t, dep[MAXN], cnt_Edge = 1, cur[MAXN], ans;
vector <int> Stop[15 + 10];
struct node{int to; LL Flow; int Next;} Edge[MAXM];

struct Union
{
	int fa[15 + 10];
	void init() {for (int i = 1; i <= n + 2; ++i) fa[i] = i;}
	int gf(int x) {return (fa[x] == x) ? x : fa[x] = gf(fa[x]);}
	void hb(int x, int y) {if (gf(x) != gf(y)) fa[fa[x]] = fa[y];}
}Plozia;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int u, int v, int Flow)
{
	++cnt_Edge; Edge[cnt_Edge] = (node){v, Flow, Head[u]}; Head[u] = cnt_Edge;
	++cnt_Edge; Edge[cnt_Edge] = (node){u, 0, Head[v]}; Head[v] = cnt_Edge;
}
int Min(int fir, int sec) {return (fir < sec) ? fir : sec;}

bool bfs()
{
	queue <int> q; q.push(s);
	memset(dep, 0, sizeof(dep)); dep[s] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].Flow == 0 || dep[u] != 0) continue ;
			dep[u] = dep[x] + 1; q.push(u);
		}
	}
	return dep[t];
}

int dfs(int now, int Flow)
{
	if (now == t || Flow == 0) return Flow;
	int used = 0;
	for (int i = cur[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to; cur[now] = i;
		if (dep[u] == dep[now] + 1 && Edge[i].Flow)
		{
			int Minn = dfs(u, Min(Edge[i].Flow, Flow - used));
			if (Minn)
			{
				Edge[i].Flow -= Minn; Edge[i ^ 1].Flow += Minn; used += Minn;
				if (used == Flow) return used;
			}
		}
	}
	if (used == 0) dep[now] = 0;
	return used;
}

int dinic()
{
	int sum = 0;
	while (bfs()) {memcpy(cur, Head, sizeof(cur)); sum += dfs(s, INF);}
	return sum;
}

signed main()
{
	n = read(), m = read(), k = read(); Plozia.init();
	for (int i = 1; i <= m; ++i)
	{
		h[i] = read(); int r = read(), las = 0;
		for (int j = 1; j <= r; ++j)
		{
			int tmp = read(); Stop[i].push_back(tmp);
			if (tmp == 0) tmp = n + 1;
			if (tmp == -1) tmp = n + 2;
			if (j != 1) Plozia.hb(tmp, las);
			las = tmp;
		}
	}
	if (Plozia.gf(n + 1) != Plozia.gf(n + 2)) {printf("0\n"); return 0; }
	s = 15 * 700 + 1; t = s + 1;
	add_Edge(s, n + 1, k); add_Edge(n + 2, t, INF);
	while (1)
	{
		++Time;
		//处理相邻时间之间的转换
		for (int i = 1; i <= n + 2; ++i) add_Edge((n + 2) * (Time - 1) + i, (n + 2) * Time + i, INF);
		//处理超源超汇
		// add_Edge(s, (n + 2) * Time + 1, INF);
		add_Edge((n + 2) * (Time + 1), t, INF);
		//处理飞船的转移
		for (int i = 1; i <= m; ++i)
		{
			int Num = Time % Stop[i].size();
			if (Num == 0) Num = Stop[i].size();
			int u = Stop[i][Num - 1];
			int v;
			if (Num == Stop[i].size()) v = Stop[i][0];
			else v = Stop[i][Num];
			if (u == 0) u = n + 1;
			if (u == -1) u = n + 2;
			if (v == 0) v = n + 1;
			if (v == -1) v = n + 2;
			add_Edge((n + 2) * (Time - 1) + u, (n + 2) * Time + v, h[i]);
		}
		//跑网络流
		ans += dinic();
		if (ans >= k) {printf("%d\n", Time); break;}
	}
	return 0;
}