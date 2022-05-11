/*
========= Plozia =========
	Author:Plozia
	Problem:P4198 楼房重建
	Date:2022/1/2
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m;
struct node
{
	int l, r, ans;
	double Maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define ans(p) tree[p].ans
	#define Maxn(p) tree[p].Maxn
}tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
double Max(double fir, double sec) { return (fir > sec) ? fir : sec; }
double Min(double fir, double sec) { return (fir < sec) ? fir : sec; }

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r; if (l == r) return ;
	int mid = (l(p) + r(p)) >> 1; Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
}

int Ask(int p, double k)
{
	if (Maxn(p) <= k) return 0;
	if (l(p) == r(p)) return (Maxn(p) > k);
	if (Maxn(p << 1) <= k) return Ask(p << 1 | 1, k);
	return ans(p) - ans(p << 1) + Ask(p << 1, k);
}

void Change(int p, int x, int k)
{
	if (l(p) == r(p) && l(p) == x) { ans(p) = 1; Maxn(p) = (double) k / x; return ; }
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) Change(p << 1, x, k); else Change(p << 1 | 1, x, k);
	Maxn(p) = Max(Maxn(p << 1), Maxn(p << 1 | 1));
	ans(p) = ans(p << 1) + Ask(p << 1 | 1, Maxn(p << 1));
}

int main()
{
	n = Read(), m = Read(); Build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read();
		Change(1, x, y);
		printf("%d\n", ans(1));
	}
	return 0;
}