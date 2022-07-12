/*
========= Plozia =========
	Author:Plozia
	Problem:CF438D The Child and Sequence
	Date:2022/7/12
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e5 + 5;
int n, a[MAXN], q;
struct node { LL sum, Maxn; } tree[MAXN << 2];
#define sum(p) tree[p].sum
#define Maxn(p) tree[p].Maxn

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }

void Update(int p) { sum(p) = sum(p << 1) + sum(p << 1 | 1); Maxn(p) = Max(Maxn(p << 1), Maxn(p << 1 | 1)); }

void Build(int p, int l, int r)
{
	if (l == r) { sum(p) = Maxn(p) = a[l]; return ; }
	int mid = (l + r) >> 1; Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	Update(p);
}

void Mod(int p, int l, int r, int x, int lp = 1, int rp = n)
{
	if (Maxn(p) < x) return ;
	if (lp == rp) { sum(p) %= x; Maxn(p) %= x; return ; }
	int mid = (lp + rp) >> 1;
	if (l <= mid) Mod(p << 1, l, r, x, lp, mid);
	if (r > mid) Mod(p << 1 | 1, l, r, x, mid + 1, rp);
	Update(p);
}

void Change(int p, int x, int k, int lp = 1, int rp = n)
{
	if (lp == rp) { sum(p) = Maxn(p) = k; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Change(p << 1, x, k, lp, mid);
	else Change(p << 1 | 1, x, k, mid + 1, rp);
	Update(p);
}

LL Ask(int p, int l, int r, int lp = 1, int rp = n)
{
	if (lp >= l && rp <= r) return sum(p);
	int mid = (lp + rp) >> 1; LL val = 0;
	if (l <= mid) val += Ask(p << 1, l, r, lp, mid);
	if (r > mid) val += Ask(p << 1 | 1, l, r, mid + 1, rp);
	return val;
}

int main()
{
	n = Read(), q = Read(); for (int i = 1; i <= n; ++i) a[i] = Read(); Build(1, 1, n);
	while (q--)
	{
		int opt = Read();
		if (opt == 1) { int l = Read(), r = Read(); printf("%lld\n", Ask(1, l, r)); }
		if (opt == 2) { int l = Read(), r = Read(), x = Read(); Mod(1, l, r, x); }
		if (opt == 3) { int x = Read(), k = Read(); Change(1, x, k); }
	}
	return 0;
}