/*
========= Plozia =========
	Author:Plozia
	Problem:CF597C Subsequences
	Date:2021/5/9
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, k, a[MAXN];
LL f[MAXN][15];
struct node
{
	int l, r;
	LL val;
}tree[15][MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void build(int p, int Tag, int l, int r)
{
	tree[Tag][p].l = l, tree[Tag][p].r = r;
	if (l == r) { tree[Tag][p].val = 0; return ; }
	int mid = (l + r) >> 1;
	build(p << 1, Tag, l, mid); build(p << 1 | 1, Tag, mid + 1, r);
	tree[Tag][p].val = tree[Tag][p << 1].val + tree[Tag][p << 1 | 1].val;
}

void add(int p, int Tag, int x, LL d)
{
	if (tree[Tag][p].l == tree[Tag][p].r && tree[Tag][p].l == x) { tree[Tag][p].val += d; return ; }
	int mid = (tree[Tag][p].l + tree[Tag][p].r) >> 1;
	if (x <= mid) add(p << 1, Tag, x, d);
	else add(p << 1 | 1, Tag, x, d);
	tree[Tag][p].val = tree[Tag][p << 1].val + tree[Tag][p << 1 | 1].val;
}

LL ask(int p, int Tag, int l, int r)
{
	if (tree[Tag][p].l >= l && tree[Tag][p].r <= r) return tree[Tag][p].val;
	int mid = (tree[Tag][p].l + tree[Tag][p].r) >> 1; LL val = 0;
	if (l <= mid) val += ask(p << 1, Tag, l, r);
	if (r > mid) val += ask(p << 1 | 1, Tag, l, r);
	return val;
}

int main()
{
	n = read(), k = read() + 1;
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) f[i][1] = 1;
	for (int i = 1; i <= k; ++i) build(1, i, 1, n);
	for (int i = 1; i <= n; ++i)
	{
		add(1, 1, a[i], 1);
		for (int j = 2; j <= k; ++j) { f[i][j] = ask(1, j - 1, 1, a[i] - 1); add(1, j, a[i], f[i][j]); }
	}
	LL ans = 0;
	for (int i = 1; i <= n; ++i) ans += f[i][k];
	printf("%lld\n", ans); return 0;
}