#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 32767 + 10;
int n, cnt, root;
LL ans;
struct node
{
	int l, r, size, val, key;
}tree[MAXN];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int Make_Node(int val)
{
	++cnt;
	tree[cnt].size = 1;
	tree[cnt].val = val;
	tree[cnt].key = rand();
	return cnt;
}

void update(int now) {tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;}

void split(int now, int val, int &x, int &y)
{
	if (!now) x = y = 0;
	else
	{
		if (tree[now].val <= val) {x = now; split(tree[now].r, val, tree[now].r, y);}
		else {y = now; split(tree[now].l, val, x, tree[now].l);}
		update(now);
	}
}

int merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (tree[x].key > tree[y].key)
	{
		tree[x].r = merge(tree[x].r, y);
		update(x); return x;
	}
	else
	{
		tree[y].l = merge(x, tree[y].l);
		update(y); return y;
	}
}

void Insert(int val)
{
	int x, y; split(root, val, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

int main()
{
	srand(time(0));
	n = read(); int t = read();
	ans = t; Insert(t);
	for (int i = 2; i <= n; ++i)
	{
		t = read();
		Insert(t);
		int x, y, z, sum = 0x7f7f7f7f;
		split(root, t - 1, x, y);
		split(y, t, y, z);
		if (tree[y].size > 1) {root = merge(merge(x, y), z); continue;}
		else
		{
			if (x != 0)
			{
				int now = x;
				while (tree[now].r) now = tree[now].r;
				sum = min(sum, abs(tree[now].val - t));
			}
			if (z != 0)
			{
				int now = z;
				while (tree[now].l) now = tree[now].l;
				sum = min(sum, abs(tree[now].val - t));
			}
		}
		ans += sum;
		root = merge(merge(x, y), z);
	}
	printf("%lld\n", ans);
	return 0;
}
