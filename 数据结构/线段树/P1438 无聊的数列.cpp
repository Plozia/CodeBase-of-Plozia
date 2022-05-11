#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, a[MAXN];
struct node
{
	int l, r;
	LL add, sum;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define a(p) tree[p].add
	#define s(p) tree[p].sum
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = 0; return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
}

void spread(int p)
{
	if (a(p))
	{
		s(p << 1) += a(p) * (r(p << 1) - l(p << 1) + 1);
		s(p << 1 | 1) += a(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1);
		a(p << 1) += a(p); a(p << 1 | 1) += a(p); a(p) = 0;
	}
}

void add(int p, int l, int r, LL k)
{
	if (l(p) >= l && r(p) <= r) {s(p) += k * (r(p) - l(p) + 1); a(p) += k; return ;}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) add(p << 1, l, r, k);
	if (r > mid) add(p << 1 | 1, l, r, k);
	s(p) = s(p << 1) + s(p << 1 | 1);
}

LL ask(int p, int l, int r)
{
	if(l(p) >= l && r(p) <= r) return s(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1;LL val = 0;
	if (l <= mid) val += ask(p << 1, l, r);
	if (r > mid) val += ask(p << 1 | 1, l, r);
	return val;
}

int main()
{
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int opt = read();
		if (opt == 1)
		{
			int l = read(), r = read(), k = read(), d = read();
			add(1, l, l, k);
			if (r > l) add(1, l + 1, r, d);
			if (r != n) add(1, r + 1, r + 1, -((LL)k + (r - l) * d));
		}
		else
		{
			int p = read();
			printf("%lld\n", ask(1, 1, p) + a[p]);
		}
	}
	return 0;
}
