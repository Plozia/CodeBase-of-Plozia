/*
========= Plozia =========
	Author:Plozia
	Problem:CF161D Distance in Tree
	Date:2021/6/20
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 5;
int n, k, Head[MAXN], cnt_Edge = 1, dis[MAXN], Size[MAXN], Maxn[MAXN], Root, Node_Cnt, book[505], tmp[MAXN], cnt_tmp;
struct node { int to, val, Next; } Edge[MAXN << 1];
bool vis[MAXN];
LL ans = 0;

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

void Get_Root(int now, int father)
{
	Size[now] = 1, Maxn[now] = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		Get_Root(u, now); Size[now] += Size[u]; Maxn[now] = Max(Maxn[now], Size[u]);
	}
	Maxn[now] = Max(Maxn[now], Node_Cnt - Maxn[now]);
	if (Maxn[now] < Maxn[Root]) Root = now;
}

void Get_Dis(int now, int father)
{
	if (dis[now] <= k) { ++cnt_tmp; tmp[cnt_tmp] = dis[now]; }
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		dis[u] = dis[now] + Edge[i].val;
		Get_Dis(u, now);
	}
}

void Solve(int now)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		dis[u] = Edge[i].val; cnt_tmp = 0; book[0] = 1;
		Get_Dis(u, now);
		for (int j = 1; j <= cnt_tmp; ++j)
			if (k >= tmp[j]) ans += (LL)book[k - tmp[j]];
		for (int j = 1; j <= cnt_tmp; ++j) ++book[tmp[j]];
	}
	memset(book, 0, sizeof(book));
}

void Divide(int now)
{
	vis[now] = 1; Solve(now);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		Maxn[Root = 0] = Node_Cnt = Size[u];
		Get_Root(u, 0); Get_Root(Root, 0); Divide(Root);
	}
}

int main()
{
	n = Read(), k = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y, 1); add_Edge(y, x, 1);
	}
	Maxn[Root = 0] = Node_Cnt = n;
	Get_Root(1, 0); Get_Root(Root, 0); Divide(Root);
	printf("%lld\n", ans); return 0;
}