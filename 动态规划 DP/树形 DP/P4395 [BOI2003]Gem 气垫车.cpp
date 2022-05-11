/*
========= Plozia =========
	Author:Plozia
	Problem:P4395 [BOI2003]Gem 气垫车
	Date:2021/5/26
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 10000 + 10;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, Head[MAXN], cnt_Edge = 1;
LL f[MAXN][70];
struct node { int to, Next; } Edge[MAXN << 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void DP(int now, int father)
{
	for (int i = 1; i <= 50; ++i) f[now][i] = i;
	bool flag = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		DP(u, now); flag = 1;
	}
	if (flag) for (int i = 1; i <= 50; ++i) f[now][i] = i;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		for (int j = 1; j <= 50; ++j)
		{
			LL sum = INF;
			for (int k = 1; k <= 50; ++k)
				if (j != k) sum = Min(sum, f[u][k]);
			f[now][j] += sum;
		}
	}
}

int main()
{
	n = Read();
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read();
		add_Edge(x, y); add_Edge(y, x);
	}
	DP(1, -1); LL ans = INF;
	for (int i = 1; i <= 50; ++i) ans = Min(ans, f[1][i]);
	printf("%lld\n", ans); return 0;
}