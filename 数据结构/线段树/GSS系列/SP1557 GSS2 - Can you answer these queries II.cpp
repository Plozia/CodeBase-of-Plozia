#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN], ans[MAXN], pre[MAXN], las[MAXN << 2];
struct node
{
	int l, r, sum, maxn, lazy_sum, lazy_maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define m(p) tree[p].maxn
	#define ls(p) tree[p].lazy_sum
	#define lm(p) tree[p].lazy_maxn
}tree[MAXN << 2];
struct query
{
	int l, r, id;
}q[MAXN];

int Max(int fir, int sec) {return (fir > sec) ? fir : sec;}

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool cmp(const query &fir, const query &sec)
{
	if (fir.r ^ sec.r) return fir.r < sec.r;
	return fir.l < sec.l;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	return ;
}

void spread(int p)
{
	m(p << 1) = Max(m(p << 1), s(p << 1) + lm(p));
	s(p << 1) += ls(p);
	lm(p << 1) = Max(lm(p << 1), ls(p << 1) + lm(p));
	ls(p << 1) += ls(p);
	m(p << 1 | 1) = Max(m(p << 1 | 1), s(p << 1 | 1) + lm(p));
	s(p << 1 | 1) += ls(p);
	lm(p << 1 | 1) = Max(lm(p << 1 | 1), ls(p << 1 | 1) + lm(p));
	ls(p << 1 | 1) += ls(p);
	lm(p) = ls(p) = 0;
}

void change(int p, int l, int r, int k)
{
	if (l(p) >= l && r(p) <= r)
	{
		s(p) += k; m(p) = Max(m(p), s(p));
		ls(p) += k; lm(p) = Max(lm(p), ls(p));
		return ;
	}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r, k);
	if (r > mid) change(p << 1 | 1, l, r, k);
	s(p) = Max(s(p << 1), s(p << 1 | 1));
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

int ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return m(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1; int val = -0x7f7f7f7f;
	if (l <= mid) val = Max(val, ask(p << 1, l, r));
	if (r > mid) val = Max(val, ask(p << 1 | 1, l, r));
	return val;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
	{
		pre[i] = las[a[i] + 100000];
		las[a[i] + 100000] = i;
	}
	build(1, 1, n);
	m = read();
	for (int i = 1; i <= m; ++i) {q[i].l = read(); q[i].r = read(); q[i].id = i;}
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, j = 1; i <= n; ++i)
	{
		change(1, pre[i] + 1, i, a[i]);
		for (; j <= m && q[j].r == i; ++j)
			ans[q[j].id] = ask(1, q[j].l, q[j].r);
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
