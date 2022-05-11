#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

const int MAXN = 5e4 + 10;
int n, m, a[MAXN];
typedef long long LL;
struct node
{
	int l, r;
	LL pre, aft, sum, maxn;//最大前缀和，最大后缀和，总和，最大子段和
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define p(p) tree[p].pre
	#define a(p) tree[p].aft
	#define s(p) tree[p].sum
	#define m(p) tree[p].maxn
	node operator + (const node &b)const
	{
		node c;
		c.l = l; c.r = b.r;
		c.pre = Max(pre, sum + b.pre);
		c.aft = Max(b.sum + aft, b.aft);
		c.sum = sum + b.sum;
		c.maxn = Max(maxn, Max(b.maxn, aft + b.pre));
		return c;
	}
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
	if (l == r) {p(p) = a(p) = s(p) = m(p) = a[l]; return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

node ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return tree[p];
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid && r > mid) return ask(p << 1, l, r) + ask(p << 1 | 1, l, r);
	if (l <= mid) return ask(p << 1, l, r);
	if (r >= mid) return ask(p << 1 | 1, l, r);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		int l = read(), r = read();
		printf ("%lld\n", ask(1, l, r).maxn);
	}
	return 0;
}
