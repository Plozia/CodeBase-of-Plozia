/*
========= Plozia =========
	Author:Plozia
	Problem:P3586 [POI2015] LOG
	Date:2022/4/27
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 5, MAXV = 1e9;
int n, q, a[MAXN], cntnode, Root;
struct node
{
	int ls, rs, sum2;
	LL sum1;
}tree[MAXN * 20];
#define ls(p) tree[p].ls
#define rs(p) tree[p].rs
#define sum1(p) tree[p].sum1
#define sum2(p) tree[p].sum2

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Change(int &p, int x, int v, int lp, int rp)
{
	if (!p) p = ++cntnode;
	if (lp == rp) { sum1(p) += 1ll * lp * v; sum2(p) += v; return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Change(ls(p), x, v, lp, mid);
	else Change(rs(p), x, v, mid + 1, rp);
	sum1(p) = sum1(ls(p)) + sum1(rs(p));
	sum2(p) = sum2(ls(p)) + sum2(rs(p));
}

LL Asksum1(int &p, int l, int r, int lp, int rp)
{
	if (!p) p = ++cntnode;
	if (lp >= l && rp <= r) return sum1(p);
	int mid = (lp + rp) >> 1; LL val = 0;
	if (l <= mid) val += Asksum1(ls(p), l, r, lp, mid);
	if (r > mid) val += Asksum1(rs(p), l, r, mid + 1, rp);
	return val;
}

LL Asksum2(int &p, int l, int r, int lp, int rp)
{
	if (!p) p = ++cntnode;
	if (lp >= l && rp <= r) return sum2(p);
	int mid = (lp + rp) >> 1; LL val = 0;
	if (l <= mid) val += Asksum2(ls(p), l, r, lp, mid);
	if (r > mid) val += Asksum2(rs(p), l, r, mid + 1, rp);
	return val;
}

int main()
{
	n = Read(), q = Read();
	Change(Root, 0, n, 0, MAXV);
	while (q--)
	{
		char ch = getchar(); while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
		if (ch == 'U')
		{
			int k = Read(), v = Read();
			Change(Root, a[k], -1, 0, MAXV);
			Change(Root, v, 1, 0, MAXV); a[k] = v;
		}
		else
		{
			int c = Read(), s = Read();
			int tmp1 = Asksum2(Root, s, MAXV, 0, MAXV);
			LL tmp2 = Asksum1(Root, 0, s - 1, 0, MAXV);
			if (tmp2 >= 1ll * s * (c - tmp1)) puts("TAK");
			else puts("NIE");
		}
	}
	return 0;
}