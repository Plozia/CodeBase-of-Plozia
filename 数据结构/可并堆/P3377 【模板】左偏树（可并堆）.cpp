/*
========= Plozia =========
	Author:Plozia
	Problem:P3377 【模板】左偏树（可并堆）
	Date:2021/9/25
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m;
struct node
{
	int Son[2], Root, val, dis;
}LeftTree[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gf(int x) { return (LeftTree[x].Root == x) ? x : (LeftTree[x].Root = gf(LeftTree[x].Root)); }

int Merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (LeftTree[x].val > LeftTree[y].val || (LeftTree[x].val == LeftTree[y].val && x > y)) std::swap(x, y);
	LeftTree[x].Son[1] = Merge(LeftTree[x].Son[1], y);
	if (LeftTree[LeftTree[x].Son[0]].dis < LeftTree[LeftTree[x].Son[1]].dis) std::swap(LeftTree[x].Son[0], LeftTree[x].Son[1]);
	LeftTree[x].dis = LeftTree[LeftTree[x].Son[1]].dis + 1;
	LeftTree[LeftTree[x].Son[0]].Root = LeftTree[LeftTree[x].Son[1]].Root = LeftTree[x].Root = x; return x;
}

void Delete(int x)
{
	LeftTree[x].val = -1;
	LeftTree[LeftTree[x].Son[0]].Root = LeftTree[x].Son[0];
	LeftTree[LeftTree[x].Son[1]].Root = LeftTree[x].Son[1];
	LeftTree[x].Root = Merge(LeftTree[x].Son[0], LeftTree[x].Son[1]);
}

int main()
{
	n = Read(), m = Read(); LeftTree[0].dis = -1;
	for (int i = 1; i <= n; ++i)
		LeftTree[i].val = Read(), LeftTree[i].Root = i;
	for (int i = 1; i <= m; ++i)
	{
		int opt = Read();
		if (opt == 1)
		{
			int x = Read(), y = Read();
			if (LeftTree[x].val == -1 || LeftTree[y].val == -1) continue ;
			int fx = gf(x), fy = gf(y);
			if (fx != fy) LeftTree[fx].Root = LeftTree[fy].Root = Merge(fx, fy);
		}
		else
		{
			int x = Read();
			if (LeftTree[x].val == -1) printf("-1\n");
			else { printf("%d\n", LeftTree[gf(x)].val); Delete(gf(x)); }
		}
	}
	return 0;
}