/*
========= Plozia =========
	Author:Plozia
	Problem:P5631 最小mex生成树
	Date:2022/3/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e6 + 5, MAXA = 1e5 + 5;
int n, m, fa[MAXN], Top, sum, Height[MAXN];
struct EDGE { int x, y, l, r; } Edge[MAXN << 2];
struct STA { int x, y, f; } sta[MAXN];
struct SGT
{
	vector <int> E;
}tree[MAXA << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Insert(int p, int l, int r, int k, int lp, int rp)
{
	if (lp >= l && rp <= r) { tree[p].E.push_back(k); return ; }
	int mid = (lp + rp) >> 1;
	if (l <= mid) Insert(p << 1, l, r, k, lp, mid);
	if (r > mid) Insert(p << 1 | 1, l, r, k, mid + 1, rp);
}

int gf(int x) { while (x != fa[x]) x = fa[x]; return x; }
void Merge(int x, int y)
{
	x = gf(x), y = gf(y);
	if (Height[x] > Height[y]) std::swap(x, y);
	sta[++Top] = (STA){x, y, Height[x] == Height[y]};
	fa[x] = y; Height[y] += sta[Top].f;
}

void dfs(int p, int l, int r)
{
	int las = Top;
	for (int i = 0; i < tree[p].E.size(); ++i)
	{
		int x = Edge[tree[p].E[i]].x, y = Edge[tree[p].E[i]].y;
		if (gf(x) == gf(y)) continue ;
		Merge(x, y); --sum;
	}
	if (sum == 1) { printf("%d\n", l); exit(0); }
	if (l < r) { int mid = (l + r) >> 1; dfs(p << 1, l, mid); dfs(p << 1 | 1, mid + 1, r); }
	while (Top > las)
	{
		STA tmp = sta[Top]; --Top;
		fa[tmp.x] = tmp.x; Height[tmp.y] -= tmp.f; ++sum;
	}
}

int main()
{
	n = Read(), m = Read(); sum = n;
	for (int i = 1; i <= n; ++i) fa[i] = i, Height[i] = 1;
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(), w = Read();
		Edge[i * 2 - 1] = (EDGE){x, y, 0, w - 1};
		Edge[i * 2] = (EDGE){x, y, w + 1, MAXA - 5};
		if (Edge[i * 2 - 1].l <= Edge[i * 2 - 1].r) Insert(1, Edge[i * 2 - 1].l, Edge[i * 2 - 1].r, i * 2 - 1, 0, MAXA - 5);
		if (Edge[i * 2].l <= Edge[i * 2].r) Insert(1, Edge[i * 2].l, Edge[i * 2].r, i * 2, 0, MAXA - 5);
	}
	dfs(1, 0, MAXA - 5); puts("100001"); return 0;
}