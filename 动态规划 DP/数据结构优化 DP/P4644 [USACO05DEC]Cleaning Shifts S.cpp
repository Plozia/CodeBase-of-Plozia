/*
========= Plozia =========
	Author:Plozia
	Problem:P4644 [USACO05DEC]Cleaning Shifts S
	Date:2021/5/6
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 10000 + 10, MAXT = 86399 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, s, t;
LL f[MAXT];
struct node { int l, r; LL val; } a[MAXN];
struct node1
{
	int l, r;
	LL minn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define m(p) tree[p].minn
}tree[MAXT << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
bool cmp(const node &fir, const node &sec) { return fir.r < sec.r; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }

void build(int p, int l, int r)//建树
{
	l(p) = l, r(p) = r;
	if (l == r) { m(p) = INF; return ; }
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	m(p) = Min(m(p << 1), m(p << 1 | 1));
}

void change(int p, int x, LL d)//单点修改
{
	if (l(p) == r(p) && l(p) == x) { m(p) = Min(m(p), d); return ;}
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) change(p << 1, x, d);
	else change(p << 1 | 1, x, d);
	m(p) = Min(m(p << 1), m(p << 1 | 1));
}

LL ask(int p, int l, int r)//区间查询
{
	if (l(p) >= l && r(p) <= r) return m(p);
	int mid = (l(p) + r(p)) >> 1; LL val = INF;
	if (l <= mid) val = Min(val, ask(p << 1, l, r));
	if (r > mid) val = Min(val, ask(p << 1 | 1, l, r));
	return val;
}

int main()
{
	n = read(), s = read() + 1, t = read() + 1;
	for (int i = 1; i <= n; ++i) a[i].l = Max(read() + 1, s), a[i].r = Min(read() + 1, t), a[i].val = (LL)read();
	std::sort(a + 1, a + n + 1, cmp);//排序
	build(1, 0, t); memset(f, 0x3f, sizeof(f)); f[s - 1] = 0; change(1, s - 1, 0);//初始化
	for (int i = 1; i <= n; ++i)
	{
		LL sum = ask(1, a[i].l - 1, a[i].r - 1);
		if (sum == INF) continue ;
		f[a[i].r] = sum + a[i].val;
		change(1, a[i].r, f[a[i].r]);
	}//转移
	if (f[t] == INF) printf("-1\n");
	else printf("%lld\n", f[t]);
	return 0;
}