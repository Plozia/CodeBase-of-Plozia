/*
========= Plozia =========
	Author:Plozia
	Problem:CF1401E Divide Square
	Date:2021/8/12
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5, MAXA = 1e6 + 5;
int n, m, cntl, cntr, cl, cr;
LL ans = 1;
struct node1 { int l, r, sum; } LTree[MAXA << 2], RTree[MAXA << 2];
struct node2 { int y, r; } Linel[MAXN];
struct node3 { int y, l; } Liner[MAXN];
struct node4 { int x, l, r; } a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp2(const node2 &fir, const node2 &sec) { return fir.r < sec.r; }
bool cmp3(const node3 &fir, const node3 &sec) { return fir.l < sec.l; }
bool cmp4(const node4 &fir, const node4 &sec) { return fir.x < sec.x; }

void LBuild(int p, int l, int r)
{
	LTree[p].l = l, LTree[p].r = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	LBuild(p << 1, l, mid); LBuild(p << 1 | 1, mid + 1, r);
}

void RBuild(int p, int l, int r)
{
	RTree[p].l = l, RTree[p].r = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	RBuild(p << 1, l, mid); RBuild(p << 1 | 1, mid + 1, r);
}

void LChange(int p, int x, int d)
{
	if (LTree[p].l == LTree[p].r) { LTree[p].sum += d; return ; }
	int mid = (LTree[p].l + LTree[p].r) >> 1;
	if (x <= mid) LChange(p << 1, x, d);
	else LChange(p << 1 | 1, x, d);
	LTree[p].sum = LTree[p << 1].sum + LTree[p << 1 | 1].sum;
}

void RChange(int p, int x, int d)
{
	if (RTree[p].l == RTree[p].r) { RTree[p].sum += d; return ; }
	int mid = (RTree[p].l + RTree[p].r) >> 1;
	if (x <= mid) RChange(p << 1, x, d);
	else RChange(p << 1 | 1, x, d);
	RTree[p].sum = RTree[p << 1].sum + RTree[p << 1 | 1].sum;
}

int LAsk(int p, int l, int r)
{
	if (LTree[p].l >= l && LTree[p].r <= r) return LTree[p].sum;
	int mid = (LTree[p].l + LTree[p].r) >> 1, val = 0;
	if (l <= mid) val += LAsk(p << 1, l, r);
	if (r > mid) val += LAsk(p << 1 | 1, l, r);
	return val;
}

int RAsk(int p, int l, int r)
{
	if (RTree[p].l >= l && RTree[p].r <= r) return RTree[p].sum;
	int mid = (RTree[p].l + RTree[p].r) >> 1, val = 0;
	if (l <= mid) val += RAsk(p << 1, l, r);
	if (r > mid) val += RAsk(p << 1 | 1, l, r);
	return val;
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i)
	{
		int y = Read(), l = Read(), r = Read();
		if (l == 0) Linel[++cntl] = (node2){y, r};
		else Liner[++cntr] = (node3){y, l};
		if (l == 0 && r == 1000000) ++ans;
	}
	for (int i = 1; i <= m; ++i) a[i].x = Read(), a[i].l = Read(), a[i].r = Read();
	std::sort(Linel + 1, Linel + cntl + 1, cmp2);
	std::sort(Liner + 1, Liner + cntr + 1, cmp3);
	std::sort(a + 1, a + m + 1, cmp4);
	LBuild(1, 0, 1000000); RBuild(1, 0, 1000000);
	for (int i = 1; i <= cntl; ++i) LChange(1, Linel[i].y, 1);
	for (int i = 1; i <= m; ++i)
	{
		if (a[i].l == 0 && a[i].r == 1000000) ++ans;
		for (; cl <= cntl && Linel[cl].r < a[i].x; ++cl) LChange(1, Linel[cl].y, -1);
		for (; cr <= cntr && Liner[cr].l <= a[i].x; ++cr) RChange(1, Liner[cr].y, 1);
		ans += (LL)RAsk(1, a[i].l, a[i].r) + (LL)LAsk(1, a[i].l, a[i].r);
	}
	printf("%lld\n", ans); return 0;
}