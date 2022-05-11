/*
========= Plozia =========
	Author:Plozia
	Problem:CF845G Shortest Path Problem?
	Date:2021/7/15
	Remarks:跟 P4151 是双倍经验
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100000 + 5, MAXM = 100000 + 5;
int n, m, Head[MAXN], cnt_Edge = 1;
LL ans, dis[MAXN], d[70];
bool book[MAXN];
struct node { int to; LL val; int Next; } Edge[MAXM << 1];

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, LL z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void Add(LL x)
{
	for (int i = 63; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (d[i] & x) x ^= d[i];
			else { d[i] = x; return ; }
		}
	}
}

void dfs(int now, LL sum)
{
	book[now] = 1; dis[now] = sum;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (!book[u]) dfs(u, sum ^ Edge[i].val);
		else Add(sum ^ Edge[i].val ^ dis[u]);
	}
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(); LL z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	dfs(1, 0); ans = dis[n];
	for (int i = 63; i >= 0; --i) ans = Min(ans, ans ^ d[i]);
	printf("%lld\n", ans); return 0;
}