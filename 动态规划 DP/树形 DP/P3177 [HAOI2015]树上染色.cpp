/*
========= Plozia =========
	Author:Plozia
	Problem:P3177 [HAOI2015]树上染色
	Date:2021/5/26
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2000 + 10;
int n, k, Head[MAXN], cnt_Edge = 1, Size[MAXN];
LL f[MAXN][MAXN], g[MAXN];
struct node { int to; LL val; int Next; } Edge[MAXN << 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, LL z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void DP(int now, int father)
{
	Size[now] = 1; f[now][0] = f[now][1] = 0;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		DP(u, now);
		for (int j = 0; j <= k; ++j) g[j] = f[now][j];
		for (int j = 0; j <= Size[now] && j <= k; ++j)
			for (int l = 0; l <= Size[u] && j + l <= k; ++l)
				f[now][j + l] = Max(f[now][j + l], g[j] + f[u][l] + (1ll * l * (k - l) + 1ll * (Size[u] - l) * (n - Size[u] - k + l)) * Edge[i].val);
		Size[now] += Size[u];
	}
}

int main()
{
	n = Read(), k = Read(); memset(f, -0x3f, sizeof(f));
	if (n - k < k) k = n - k;
	for (int i = 1; i < n; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		add_Edge(x, y, z); add_Edge(y, x, z);
	}
	DP(1, -1); printf("%lld\n", f[1][k]); return 0;
}