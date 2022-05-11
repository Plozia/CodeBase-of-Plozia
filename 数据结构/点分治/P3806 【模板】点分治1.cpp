/*
========= Plozia =========
	Author:Plozia
	Problem:P3806 【模板】点分治1
	Date:2021/6/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e4 + 5;
int n, m, Head[MAXN], cnt_Edge = 1, q[MAXN], Root, Size[MAXN], dis[MAXN], Maxn[MAXN], tmp[MAXN], cnt_tmp, sum;
struct node { int to, val, Next; } Edge[MAXN << 1];
bool ans[MAXN], book[10000000 + 5], vis[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ '0');
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void Get_Root(int now, int father)
{
	Size[now] = 1, Maxn[now] = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		Get_Root(u, now);
		Size[now] += Size[u];
		Maxn[now] = Max(Maxn[now], Size[u]);
	}
	Maxn[now] = Max(Maxn[now], sum - Maxn[now]);
	if (Maxn[now] < Maxn[Root]) Root = now;
}

using std::queue;

void Get_Dis(int now, int father)
{
	if (dis[now] <= 10000000) tmp[++cnt_tmp] = dis[now];
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father || vis[u]) continue ;
		dis[u] = dis[now] + Edge[i].val;
		Get_Dis(u, now);
	}
}

void Solve(int now)
{
	queue <int> que;
	for (int _ = Head[now]; _; _ = Edge[_].Next)
	{
		int u = Edge[_].to;
		if (vis[u]) continue ;
		cnt_tmp = 0; dis[u] = Edge[_].val;
		Get_Dis(u, now);
		for (int i = 1; i <= cnt_tmp; ++i)
			for (int j = 1; j <= m; ++j)
				if (q[j] >= tmp[i]) ans[j] |= book[q[j] - tmp[i]];
		for (int i = 1; i <= cnt_tmp; ++i)
		{
			que.push(tmp[i]); book[tmp[i]] = 1;
		}
	}
	while (!que.empty())
	{
		book[que.front()] = 0; que.pop();
	}
}

void Divide(int now)
{
	vis[now] = 1; book[0] = 1;
	Solve(now);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		Maxn[Root = 0] = sum = Size[u];
		Get_Root(u, 0); Get_Root(Root, 0);
		Divide(Root);
	}
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	for (int i = 1; i <= m; ++i) q[i] = Read();
	Maxn[Root = 0] = sum =  n;
	Get_Root(1, 0); Get_Root(Root, 0);
	Divide(Root);
	for (int i = 1; i <= m; ++i)
		if (ans[i]) printf("AYE\n");
		else printf("NAY\n");
	return 0;
}