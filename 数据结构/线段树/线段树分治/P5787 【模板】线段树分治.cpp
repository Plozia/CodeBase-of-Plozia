/*
========= Plozia =========
	Author:Plozia
	Problem:P5787 二分图 /【模板】线段树分治
	Date:2022/3/27
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;
using std::stack;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m, k, cnt, ans[MAXN], fa[MAXN << 1], Height[MAXN << 1];
struct node { int x, y, l, r; } Edge[MAXN << 1];
struct STA { int x, y, h; } ;
struct SgT
{
	vector <int> E;
}tree[MAXN << 2];
stack <STA> sta;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gf(int x) { while (fa[x] != x)  x = fa[x]; return x; }

void Insert(int p, int l, int r, int Num, int lp, int rp)
{
	if (lp >= l && rp <= r) { tree[p].E.push_back(Num); return ; }
	int mid = (lp + rp) >> 1;
	if (l <= mid) Insert(p << 1, l, r, Num, lp, mid);
	if (r > mid) Insert(p << 1 | 1, l, r, Num, mid + 1, rp);
}

void Merge(int x, int y)
{
	x = gf(x), y = gf(y);
	if (Height[x] > Height[y]) std::swap(x, y);
	sta.push((STA){x, y, Height[x] == Height[y]});
	fa[x] = y; Height[y] += (Height[x] == Height[y]);
}

void dfs(int p, int lp, int rp)
{
	int cnt = 0, flag = 0;
	for (int i = 0; i < tree[p].E.size(); ++i)
	{
		int x = Edge[tree[p].E[i]].x, y = Edge[tree[p].E[i]].y;
		if (gf(x) == gf(y))
		{
			for (int j = lp; j <= rp; ++j) ans[j] = 1;
			flag = 1; break ;
		}
		if (gf(x) != gf(y + n)) Merge(x, y + n), ++cnt;
		if (gf(y) != gf(x + n)) Merge(y, x + n), ++cnt;
	}
	if (lp < rp && !flag) { int mid = (lp + rp) >> 1; dfs(p << 1, lp, mid); dfs(p << 1 | 1, mid + 1, rp); }
	while (cnt--)
	{
		STA tmp = sta.top(); sta.pop();
		fa[tmp.x] = tmp.x; Height[tmp.y] -= tmp.h;
	}
}

int main()
{
	n = Read(), m = Read(), k = Read();
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(), l = Read(), r = Read();
		Edge[i] = (node){x, y, l + 1, r};
		if (l + 1 <= r) Insert(1, l + 1, r, i, 1, k);
	}
	for (int i = 1; i <= n * 2; ++i) fa[i] = i, Height[i] = 1;
	dfs(1, 1, k);
	for (int i = 1; i <= k; ++i) puts((ans[i] == 0) ? ("Yes") : ("No"));
	return 0;
}