/*
========= Plozia =========
	Author:Plozia
	Problem:P4149 [IOI2011]Race
	Date:2021/6/21
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 2e5 + 5, MAXK = 1e6 + 5, INF = 0x7f7f7f7f;
int n, k, ans, Head[MAXN], cnt_Edge = 1, tmp1[MAXN], tmp2[MAXN], cnt_tmp, Size[MAXN], Maxn[MAXN], Node_Cnt, Root, book[MAXK];
LL dis[MAXN];
bool vis[MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];

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

void Get_Dis(int now, int father, int depth)
{
	if (dis[now] <= k) { ++cnt_tmp; tmp1[cnt_tmp] = dis[now]; tmp2[cnt_tmp] = depth; }
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		dis[u] = dis[now] + (LL)Edge[i].val;
		Get_Dis(u, now, depth + 1);
	}
}

void Solve(int now)
{
	queue <int> q;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		cnt_tmp = 1; tmp1[1] = 0; tmp2[1] = 0; dis[u] = Edge[i].val;
		Get_Dis(u, now, 1);
		for (int j = 1; j <= cnt_tmp; ++j)
			if (k >= tmp1[j]) ans = Min(ans, tmp2[j] + book[k - tmp1[j]]);
		for (int j = 1; j <= cnt_tmp; ++j)
			{ q.push(tmp1[j]); book[tmp1[j]] = Min(book[tmp1[j]], tmp2[j]); }
	}
	while (!q.empty()) { book[q.front()] = 0x3f3f3f3f; q.pop(); }
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
	n = Read(), k = Read(); ans = INF;
	memset(book, 0x3f, sizeof(book));
	for (int i = 1; i < n; ++i)
	{
		int x = Read() + 1, y = Read() + 1, z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	Maxn[Root = 0] = Node_Cnt = n;
	Get_Root(1, 0); Get_Root(Root, 0); Divide(Root);
	if (ans >= n) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}