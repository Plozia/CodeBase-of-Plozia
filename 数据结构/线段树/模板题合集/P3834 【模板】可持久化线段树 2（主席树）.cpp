#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int n, m, a[MAXN], b[MAXN], cntn, root[MAXN], cnt;
struct node
{
	int ls, rs, sum;
}tree[(MAXN << 4) + (MAXN << 2)];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int build(int p, int l, int r)
{
	p = ++cnt;
	if (l == r) return p;
	int mid = (l + r) >> 1;
	tree[p].ls = build(tree[p].ls, l, mid);
	tree[p].rs = build(tree[p].rs, mid + 1, r);
	return p;
}

int change(int p, int l, int r, int x)
{
	int rt = ++cnt;
	tree[rt] = tree[p]; tree[rt].sum++;
	int mid = (l + r) >> 1;
	if (l == r) return rt;
	if (x <= mid) tree[rt].ls = change(tree[p].ls, l, mid, x);
	else tree[rt].rs = change(tree[p].rs, mid + 1, r, x);
	return rt;
}

int ask(int p1, int p2, int l, int r, int k)
{
	if (l == r) return l;
	int sum = tree[tree[p2].ls].sum - tree[tree[p1].ls].sum, mid = (l + r) >> 1;
	if (sum >= k) return ask(tree[p1].ls, tree[p2].ls, l, mid, k);
	else return ask(tree[p1].rs, tree[p2].rs, mid + 1, r, k - sum);
}

int main()
{
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) b[i] = a[i] = read();
	sort(b + 1, b + n + 1); root[0] = build(1, 1, n);
	cntn = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; ++i)
	{
		a[i] = lower_bound(b + 1, b + cntn + 1, a[i]) - b;
		root[i] = change(root[i - 1], 1, cntn, a[i]);
	}
	for (int i = 1; i <= m; ++i)
	{
		int l = read(), r = read(), k = read();
		int p = ask(root[l - 1], root[r], 1, cntn, k);
		printf("%d\n", b[p]);
	}
	return 0;
}
