/*
========= Plozia =========
	Author:Plozia
	Problem:P3747 [六省联考 2017] 相逢是问候
	Date:2021/5/19
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 10;
int n, m, p, c, phi = 1, a[MAXN];
struct node
{
	int l, r;
	LL sum, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define a(p) tree[p].add
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

LL ksm(LL a, LL b, LL p)
{
	LL ans = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) ans = ans * a % p;
	return ans;
}

void Get_Phi()
{
	int c = p;
	for (int i = 2; i * i <= c; ++i)
	{
		int sum = 0;
		while (c % i == 0) { ++sum; c /= i; }
		if (sum != 0) phi *= (i - 1) * ksm(i, sum - 1, p);
	}
	if (c != 1) phi *= (c - 1);
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { s(p) = a[l]; return ; }
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);  build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
}

int main()
{
	n = read(), m = read(), p = read(), c = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build (1, 1, n);
}