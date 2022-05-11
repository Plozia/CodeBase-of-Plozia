#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 10, P = 998244353;
int n, a[MAXN], cnt, root;
LL ans, f[MAXN];

struct node
{
	int l, r, size, val, key;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int Make_Node(int val)
{
	int now = ++cnt;
	tree[now].size = 1;
	tree[now].val = val;
	return now;
}

void update(int x) {tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + 1;}

void split(int now, int val, int &x, int &y)
{
	if (now == 0) x = y = 0;
	else
	{
		if (tree[now].val <= val)
		{
			x = now;
			split(tree[now].r, val, tree[now].r, y);
		}
		else
		{
			y = now;
			split(tree[now].l, val, x, tree[now].l);
		}
		update(now);
	}
}

int merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (rand() & 1)
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
	int x, y; split(root, val - 1, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

int Find(int val)
{
	int x, y, ans;
	split(root, val - 1, x, y);
	ans = tree[x].size;
	root = merge(x, y);
	return ans;
}

int main()
{
	srand(time(0));
	n = read(); f[0] = 1; cnt = root = 0;
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % P;
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		Insert(a[i]); ans = (ans + ((LL)a[i] - 1 - Find(a[i])) * f[n - i]) % P;
//		printf("%d/%d/%d\n", f[n - i], Find(a[i]), ans);
	}
	printf("%lld\n", ans + 1);
	return 0;
}
