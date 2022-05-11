/*
========= Plozia =========
	Author:Plozia
	Problem:P3623 [APIO2008]免费道路
	Date:2021/4/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 20000 + 10, MAXM = 100000 + 10;
int n, m, k;
struct node { int x, y, z; } a[MAXM];
struct Union
{
	int fa[MAXN];
	void init() { for (int i = 1; i <= n; ++i) fa[i] = i; }
	int gf(int x) { return (fa[x] == x) ? x : fa[x] = gf(fa[x]); }
	void hb(int x, int y) { if (gf(x) != gf(y)) fa[fa[x]] = fa[y]; }
}u;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
bool cmp1(const node &fir, const node &sec) { return fir.z < sec.z; }
bool cmp2(const node &fir, const node &sec) { return fir.z > sec.z; }

int main()
{
	n = read(), m = read(), k = read();
	for (int i = 1; i <= m; ++i) a[i].x = read(), a[i].y = read(), a[i].z = read() ^ 1;
	std::sort(a + 1, a + m + 1, cmp1);
	u.init(); int tmp, sum;
	tmp = 0, sum = n;
	for (int i = 1; i <= m; ++i)
	{
		if (u.gf(a[i].x) != u.gf(a[i].y))
		{
			u.hb(a[i].x, a[i].y);
			if (a[i].z == 1) a[i].z = -1, ++tmp;
			--sum; if (sum == 1) break ;
		}
	}
	if (tmp > k) { printf("no solution\n"); return 0; }
	if (sum != 1) { printf ("no solution\n"); return 0; }
	std::sort(a + 1, a + m + 1, cmp2);
	u.init(); sum = n;
	for (int i = 1; i <= m; ++i)
		if (a[i].z == -1) { --sum; u.hb(a[i].x, a[i].y); }
	for (int i = 1; i <= m; ++i)
	{
		if (sum == 1) break ;
		if (a[i].z == -1) continue ;
		if (tmp == k && a[i].z == 1) continue ;
		if (u.gf(a[i].x) != u.gf(a[i].y))
		{
			u.hb(a[i].x, a[i].y);
			if (a[i].z == 1) ++tmp, a[i].z = -1;
			if (a[i].z == 0) a[i].z = -2;
			--sum; if (sum == 1) break ;
		}
	}
	if (tmp != k) { printf("no solution\n"); return 0; }
	for (int i = 1; i <= m; ++i)
	{
		if (a[i].z == -2) printf("%d %d 1\n", a[i].x, a[i].y);
		if (a[i].z == -1) printf("%d %d 0\n", a[i].x, a[i].y);
	}
	return 0;
}