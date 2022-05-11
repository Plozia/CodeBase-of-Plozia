/*
========= Plozia =========
	Author:Plozia
	Problem:CF833B The Bakery
	Date:2022/4/29
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3.5e4 + 5;
int n, k, a[MAXN], f[MAXN][55], Pre[MAXN], book[MAXN];
struct node
{
	int tag, Maxn;
}tree[MAXN << 2];
#define tag(p) tree[p].tag
#define Maxn(p) tree[p].Maxn

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Update(int p) { Maxn(p) = Max(Maxn(p << 1), Maxn(p << 1 | 1)); }
void Spread(int p)
{
	if (tag(p))
	{
		Maxn(p << 1) += tag(p); Maxn(p << 1 | 1) += tag(p);
		tag(p << 1) += tag(p); tag(p << 1 | 1) += tag(p);
		tag(p) = 0;
	}
}

void Change(int p, int x, int v, int lp, int rp)
{
	tag(p) = 0; if (lp == rp) { Maxn(p) = v; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Change(p << 1, x, v, lp, mid);
	else Change(p << 1 | 1, x, v, mid + 1, rp);
	Update(p);
}
void Add(int p, int l, int r, int v, int lp, int rp)
{
	if (lp >= l && rp <= r) { Maxn(p) += v; tag(p) += v; return ; }
	Spread(p); int mid = (lp + rp) >> 1;
	if (l <= mid) Add(p << 1, l, r, v, lp, mid);
	if (r > mid) Add(p << 1 | 1, l, r, v, mid + 1, rp);
	Update(p);
}
int Ask(int p, int l, int r, int lp, int rp)
{
	if (lp >= l && rp <= r) return Maxn(p);
	Spread(p); int mid = (lp + rp) >> 1, val = 0;
	if (l <= mid) val = Max(val, Ask(p << 1, l, r, lp, mid));
	if (r > mid) val = Max(val, Ask(p << 1 | 1, l, r, mid + 1, rp));
	return val;
}

int main()
{
	n = Read(), k = Read(); for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i <= n; ++i)
	{
		if (!book[a[i]]) book[a[i]] = i;
		else { Pre[i] = book[a[i]]; book[a[i]] = i; }
	}
	for (int j = 1; j <= k; ++j)
	{
		for (int i = 1; i <= n; ++i) Change(1, i, f[i][j - 1], 0, n);
		for (int i = 1; i <= n; ++i)
		{
			Add(1, Pre[i], i - 1, 1, 0, n);
			f[i][j] = Ask(1, j - 1, i - 1, 0, n);
		}
	}
	printf("%d\n", f[n][k]); return 0;
}