#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
int n, m, a[MAXN], root[MAXN], cnt;
struct node
{
	int ls, rs, val;
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
	if (l == r) {tree[p].val = a[l]; return cnt;}
	int mid = (l + r) >> 1;
	tree[p].ls = build(tree[p].ls, l, mid);
	tree[p].rs = build(tree[p].rs, mid + 1, r);
	return p;
}

int change(int p, int l, int r, int loc, int val)
{
	tree[++cnt] = tree[p];
	p = cnt;
	if (l == r) tree[p].val = val;
	else
	{
		int mid = (l + r) >> 1;
		if (loc <= mid) tree[p].ls = change(tree[p].ls, l, mid, loc, val);
		else tree[p].rs = change(tree[p].rs, mid + 1, r, loc, val);
	}
	return p;
}

int ask(int p, int l, int r, int loc)
{
	if (l == r) return tree[p].val;
	int mid = (l + r) >> 1;
	if (loc <= mid) return ask(tree[p].ls, l, mid, loc);
	else return ask(tree[p].rs, mid + 1, r, loc);
}

int main()
{
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	root[0] = build(0, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int v = read(), opt = read(), loc = read();
		if (opt == 1)
		{
			int val = read();
			root[i] = change(root[v], 1, n, loc, val);
		}
		else
		{
			printf("%d\n", ask(root[v], 1, n, loc));
			root[i] = root[v];
		}
	}
	return 0;
}
