#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int Max(LL fir, LL sec) {return (fir > sec) ? fir : sec;}
int Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}

const int MAXN = 1e4 + 10;
int t, n, m, a[MAXN];
struct node
{
	int l, r;
	LL sum, pre, aft, maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define p(p) tree[p].pre
	#define a(p) tree[p].aft
	#define m(p) tree[p].maxn
	node operator + (const node &b)
	{
		node c;
		c.l = l, c.r = b.r;
		c.sum = sum + b.sum;
		c.pre = Max(pre, sum + b.pre);
		c.aft = Max(b.aft, b.sum + aft);
		c.maxn = Max(maxn, Max(b.maxn, aft + b.pre));
		return c;
	}
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = a(p) = p(p) = m(p) = a[l]; return ;}
	int mid = (l(p) + r(p)) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

node Ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return tree[p];
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid && r > mid) return Ask(p << 1, l, r) + Ask(p << 1 | 1, l, r);
	if (l <= mid) return Ask(p << 1, l, r);
	if (r > mid) return Ask(p << 1 | 1, l, r);
}

int main()
{
	t = read();
	while (t--)
	{
		memset(a, 0, sizeof(a)); memset(tree, 0, sizeof(tree));
		n = read();
		for (int i = 1; i <= n; ++i) a[i] = read();
		build(1, 1, n); m = read();
		for (int i = 1; i <= m; ++i)
		{
			int l1 = read(), r1 = read(), l2 = read(), r2 = read(); LL ans;
			if (r1 <= l2) ans = Ask(1, r1, l2).sum + Ask(1, l1, r1).aft + Ask(1, l2, r2).pre - a[r1] - a[l2];
			else
			{
				ans = Ask(1, l1, l2).aft + Ask(1, l2, r1).pre - a[l2];
				ans = Max(ans, Ask(1, l1, l2).aft + Ask(1, l2, r1).sum + Ask(1, r1, r2).pre - a[l2] - a[r1]);
				ans = Max(ans, Ask(1, l2, r1).maxn);
				ans = Max(ans, Ask(1, l2, r1).aft + Ask(1, r1, r2).pre - a[r1]);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
