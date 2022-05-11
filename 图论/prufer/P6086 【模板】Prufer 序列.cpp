/*
========= Plozia =========
	Author:Plozia
	Problem:P6086 【模板】Prufer 序列
	Date:2022/2/12
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 5e6 + 5;
int n, opt, fa[MAXN], Prufer[MAXN], d[MAXN], Head[MAXN], cnt_Edge = 1;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
struct node { int To, Next; } Edge[MAXN << 1];
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void TreeToPrufer()
{
	for (int i = 1; i < n; ++i) fa[i] = Read(), ++d[i], ++d[fa[i]];
	priority_queue <int> q;
	for (int i = 1; i <= n; ++i) if (d[i] == 1) q.push(-i);
	for (int i = 1; i <= n - 2; ++i)
	{
		int x = -q.top(); q.pop();
		Prufer[++Prufer[0]] = fa[x]; --d[fa[x]];
		if (d[fa[x]] == 1) q.push(-fa[x]);
	}
	LL ans = 0;
	for (int i = 1; i <= n - 2; ++i) ans ^= 1ll * i * Prufer[i];
	printf("%lld\n", ans);
}

void dfs(int now, int father)
{
	fa[now] = father;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		dfs(u, now);
	}
}

void PruferToTree()
{
	for (int i = 1; i <= n - 2; ++i) Prufer[i] = Read(), ++d[Prufer[i]];
	for (int i = 1; i <= n; ++i) ++d[i];
	priority_queue <int> q;
	for (int i = 1; i <= n; ++i) if (d[i] == 1) q.push(-i);
	for (int i = 1; i <= n - 2; ++i)
	{
		int x = -q.top(); q.pop();
		add_Edge(x, Prufer[i]); add_Edge(Prufer[i], x);
		--d[Prufer[i]]; if (d[Prufer[i]] == 1) q.push(-Prufer[i]);
	}
	int p1 = -q.top(); q.pop();
	add_Edge(p1, n); add_Edge(n, p1);
	dfs(n, n); LL ans = 0;
	for (int i = 1; i < n; ++i) ans ^= 1ll * i * fa[i];
	printf("%lld\n", ans);
}

int main()
{
	n = Read(), opt = Read();
	if (opt == 1) TreeToPrufer();
	else PruferToTree();
	return 0;
}