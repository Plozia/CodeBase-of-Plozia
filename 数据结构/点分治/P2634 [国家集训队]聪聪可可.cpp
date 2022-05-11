/*
========= Plozia =========
	Author:Plozia
	Problem:P2634 [国家集训队]聪聪可可
	Date:2021/6/20
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e4 + 10;
int n, Head[MAXN], cnt_Edge = 1, tmp[3], Size[MAXN], Maxn[MAXN], Root, dis[MAXN], Node_Cnt;
struct node { int to, val, Next; } Edge[MAXN << 1];
bool vis[MAXN];
LL ans, ans2, book[3];

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
int gcd(int x, int y) { return (y == 0) ? x : gcd(y, x % y); }

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
	++tmp[dis[now]];
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u] || u == father) continue ;
		((dis[u] = dis[now] + Edge[i].val) >= 3) ? (dis[u] %= 3) : 0;
		Get_Dis(u, now);
	}
}

void Solve(int now)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (vis[u]) continue ;
		tmp[0] = tmp[1] = tmp[2] = 0; dis[u] = Edge[i].val;
		Get_Dis(u, now);
		ans += 2ll * tmp[0] * book[0] + 2ll * tmp[1] * book[2] + 2ll * tmp[2] * book[1];
		book[0] += tmp[0]; book[1] += tmp[1]; book[2] += tmp[2];
	}
	ans += book[0] * 2; book[0] = book[1] = book[2] = 0;
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
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read() % 3;
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	Maxn[Root = 0] = Node_Cnt = n;
	Get_Root(1, 0); Get_Root(Root, 0); Divide(Root);
	ans2 = n * n; ans += n; LL g = gcd(ans, ans2);
	ans /= g; ans2 /= g; printf("%lld/%lld\n", ans, ans2); return 0;
}