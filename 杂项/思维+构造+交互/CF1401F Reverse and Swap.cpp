/*
========= Plozia =========
	Author:Plozia
	Problem:CF1401F Reverse and Swap
	Date:2022/5/20
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = (1 << 18) + 5;
int n, a[MAXN], q, rev[20];
struct SgT { LL sum; int dep; } tree[MAXN << 2];
#define dep(p) tree[p].dep
#define sum(p) tree[p].sum
#define ls(p) ((rev[dep(p)]) ? (p << 1 | 1) : (p << 1))
#define rs(p) ((rev[dep(p)]) ? (p << 1) : (p << 1 | 1))

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void Update(int p) { sum(p) = sum(ls(p)) + sum(rs(p)); }

void Build(int p, int l, int r, int d)
{
	dep(p) = d;
	if (l == r) { sum(p) = a[l]; return ; }
	int mid = (l + r) >> 1; Build(ls(p), l, mid, d + 1); Build(rs(p), mid + 1, r, d + 1);
	Update(p);
}

void Change(int p, int x, int k, int lp, int rp)
{
	if (lp == rp) { sum(p) = k; return ; }
	int mid =  (lp + rp) >> 1;
	if (x <= mid) Change(ls(p), x, k, lp, mid);
	else Change(rs(p), x, k, mid + 1, rp);
	Update(p);
}

LL Ask(int p, int l, int r, int lp, int rp)
{
	if (lp >= l && rp <= r) return sum(p);
	int mid = (lp + rp) >> 1; LL val = 0;
	if (l <= mid) val += Ask(ls(p), l, r, lp, mid);
	if (r > mid) val += Ask(rs(p), l, r, mid + 1, rp);
	return val;
}

int main()
{
	int m = Read(); n = (1 << m), q = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	Build(1, 1, n, 0);
	while (q--)
	{
		int opt = Read();
		if (opt == 1) { int x = Read(), k = Read(); Change(1, x, k, 1, n); }
		if (opt == 4) { int l = Read(), r = Read(); printf("%lld\n", Ask(1, l, r, 1, n)); }
		if (opt == 3) { int x = Read(); if (x != m) rev[m - x - 1] ^= 1; }
		if (opt == 2) { int x = Read(); for (int i = m - x; i <= m; ++i) rev[i] ^= 1; }
	}
	return 0;
}