/*
========= Plozia =========
	Author:Plozia
	Problem:P5227 [AHOI2013]连通图
	Date:2022/3/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m, fa[MAXN], Height[MAXN], sum, Top, cntEdge, ans[MAXN];
vector <int> v[MAXN << 1];
struct node { int x, y; } a[MAXN << 1];
struct EDGE { int x, y, l, r; } Edge[MAXN << 3];
struct STA { int x, y, f; } sta[MAXN << 3];
struct SgT
{
	vector <int> E;
}tree[MAXN << 2];

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
	if (Height[x] > Height[y]) std::swap(x, y);
	sta[++Top] = (STA){x, y, Height[x] == Height[y] };
	fa[x] = y; Height[y] += sta[Top].f;
}

void dfs(int p, int l, int r)
{
	int las = Top;
	for (int i = 0; i < tree[p].E.size(); ++i)
	{
		int x = gf(Edge[tree[p].E[i]].x), y = gf(Edge[tree[p].E[i]].y);
		if (x == y) continue; Merge(x, y); --sum;
	}
	if (l == r) ans[l] = sum;
	else { int mid = (l + r) >> 1; dfs(p << 1, l, mid); dfs(p << 1 | 1, mid + 1, r); }
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
	for (int i = 1; i <= m; ++i) a[i].x = Read(), a[i].y = Read();
	int k = Read();
	for (int i = 1; i <= k; ++i)
	{
		int c = Read();
		while (c--) { int tmp = Read(); v[tmp].push_back(i); }
	}
	for (int i = 1; i <= m; ++i)
	{
		v[i].push_back(0); v[i].push_back(k + 1);
		std::sort(v[i].begin(), v[i].end());
		for (int j = 1; j < v[i].size(); ++j)
		{
			if (v[i][j - 1] + 1 <= v[i][j] - 1)
			{
				Edge[++cntEdge] = (EDGE){a[i].x, a[i].y, v[i][j - 1] + 1, v[i][j] - 1};
				Insert(1, v[i][j - 1] + 1, v[i][j] - 1, cntEdge, 1, k);
			}
		}
	}
	dfs(1, 1, k);
	for (int i = 1; i <= k; ++i) puts((ans[i] == 1) ? "Connected" : "Disconnected");
	return 0;
}